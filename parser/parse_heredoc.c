#include "../minishell.h"

int	heredoc_is_infile(struct s_tokens *token)
{
	int	is_infile;

	is_infile = 1;
	while (token && token->type != TOKEN_PIPE)
	{
		if (token->type == TOKEN_HEREDOC || token->type == TOKEN_REDIR_INPUT)
		{
			is_infile = 0;
			break ;
		}
		token = token->next;
	}
	return (is_infile);
}

void	read_heredoc_not_infile(char *limiter, struct s_program_info *program,
			struct s_commands *new_command)
{
	char	*line;

	line = NULL;
	while (!line || ((ft_strlen(line) - 1) != ft_strlen(limiter)
			|| ft_strncmp(line, limiter, ft_strlen(limiter))))
	{
		if (line)
			free(line);
		ft_printf(">");
		line = get_next_line(0); // prot
		if (!line)
		{
			commands_list_destroy(new_command);
			alloc_handling(NULL, program);
		}
	}
	free(line);
}

void	handle_heredoc_error(struct s_program_info *program, struct s_commands *new_command, int fd[2], char *line)
{
	if (fd[0] != -1)
		close(fd[0]);
	if (fd[1] != -1)
		close(fd[1]);
	if (line)
		free(line);
	if (new_command)
		commands_list_destroy(new_command);
	alloc_handling(NULL, program);
}

void	expand_heredoc_line(struct s_program_info *program, struct s_commands *new_command, int fd[2], char **line)
{
	char	*tmp;

	tmp = *line;
	program->expander = ft_calloc(1, sizeof(struct s_expander_info)); // prot
	if (!program->expander)
		handle_heredoc_error(program, new_command, fd, *line);
	initialize_expander_info(program, *line, 1);
	*line = ft_strdup(program->expander->expanded_str); // prot
	if (!(*line))
		handle_heredoc_error(program, new_command, fd, *line);
	free(tmp);
	destroy_expander_info(program->expander);
	program->expander = NULL;
}

int	read_heredoc_infile(char *limiter, struct s_program_info *program,
		int expand_heredoc_content, struct s_commands *new_command)
{
	char	*line;
	int		fd[2];

	handle_syserror(pipe(fd), program); // prot
	line = NULL;
	while (!line || ((ft_strlen(line) - 1) != ft_strlen(limiter)
			|| ft_strncmp(line, limiter, ft_strlen(limiter))))
	{
		if (line)
			free(line);
		ft_printf("> ");
		line = get_next_line(0); // prot
		if (!line)
                	handle_heredoc_error(program, new_command, fd, line);
		if ((ft_strlen(line) - 1) != ft_strlen(limiter)
				|| ft_strncmp(line, limiter, ft_strlen(limiter)))
		{
			if (expand_heredoc_content)
				expand_heredoc_line(program, new_command, fd, &line);
			write(fd[1], line, ft_strlen(line));
		}
	}
	free(line);
	close(fd[1]);
	return (fd[0]);
}

void	parse_heredoc(struct s_tokens *token, struct s_commands *new_command,
		struct s_program_info *program)
{
	int	expand_heredoc_content;
	char	*tmp;

	expand_heredoc_content = !(ft_strchr(token->content, '\'') || 
					ft_strchr(token->content, '\"'));
	tmp = token->content;
	token->content = remove_quotes_from_token(program, token);
	free(tmp);
	if (heredoc_is_infile(token))
		new_command->heredoc_fd = read_heredoc_infile(token->content, program,
						expand_heredoc_content, new_command);
	else
		read_heredoc_not_infile(token->content, program, new_command);
}
