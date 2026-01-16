#include "../minishell.h"

const char *redir_type_to_str(enum e_redirection_type type) // delete
{
    if (type == INFILE)
        return ("INFILE");
    if (type == OUTFILE_TRUNCATE)
        return ("OUTFILE_TRUNCATE");
    if (type == OUTFILE_APPEND)
        return ("OUTFILE_APPEND");
    return ("UNKNOWN");
}


void print_args(char **args)//delete
{
    int i;

    if (!args)
    {
        printf("  Args         : (none)\n");
        return;
    }

    printf("  Args         :\n");
    i = 0;
    while (args[i])
    {
        printf("    [%d] %s\n", i, args[i]);
        i++;
    }
}

void print_redirections(struct s_redirections_files *files)//delete
{
    if (!files)
    {
        printf("  Redirections : (none)\n");
        return;
    }

    printf("  Redirections :\n");
    while (files)
    {
        printf("    -> %-18s : %s\n",
               redir_type_to_str(files->type),
               files->name);
        files = files->next;
    }
}

void    read_heredoc_test(int fd) // delete
{
        char buffer[1];

        while (read(fd, buffer, 1))
        {
                printf("%c", buffer[0]);
        }
}

void print_commands(struct s_commands *cmds)//delete
{
    int i;

    i = 1;
    while (cmds)
    {
        printf("\n================ COMMAND %d ================\n", i);
//        printf("  Path         : %s\n",
//             cmds->absolute_path ? cmds->absolute_path : "(null)");
        print_args(cmds->command_args);
        printf("  Heredoc FD   : %d\n", cmds->heredoc_fd);
	printf("  Heredoc DATA :\n");
	if (cmds->heredoc_fd != -1)
	read_heredoc_test(cmds->heredoc_fd);
        print_redirections(cmds->files_list);
        printf("===========================================\n");

        cmds = cmds->next;
        i++;
    }
}

int	count_command_args(struct s_tokens *token)
{
	int	count;

	count = 0;
	while (token && token->type != TOKEN_PIPE)
	{
		if (token->type == TOKEN_WORD)
			if (!token->previous || token->previous->type == TOKEN_WORD
				|| token->previous->type == TOKEN_PIPE)
				count++;
		token = token->next;
	}
	return (count);
}

int	get_file_type(enum e_token_type type)
{
	if (type == TOKEN_REDIR_OUTPUT)
		return (OUTFILE_TRUNCATE);
	if (type == TOKEN_REDIR_APPEND)
		return (OUTFILE_APPEND);
	if (type == TOKEN_REDIR_INPUT)
		return (INFILE);
	return (-1);
}

void	parse_redirections(struct s_tokens *token,
		struct s_commands *new_command, struct s_program_info *program)
{
	struct s_redirections_files	*new_file;
	char						*file_name;
	int							file_type;

	if (token->previous->type >= TOKEN_REDIR_OUTPUT
		&& token->previous->type <= TOKEN_REDIR_INPUT)
	{
		file_type = get_file_type(token->previous->type);
		file_name = alloc_handling(ft_strdup(token->content), program);
		new_file = files_list_new_node(file_name, file_type);
		if (!new_file)
		{
			free(file_name);
			alloc_handling(NULL, program);
		}
		files_list_add_back(&new_command->files_list, new_file);
	}
	else if (token->previous->type == TOKEN_HEREDOC)
		parse_heredoc(token, new_command, program);
}

void	parser(struct s_program_info *program)
{
	struct s_tokens		*token;
	struct s_commands	*new_command;
	int					i;

	token = program->tokens_list;
	while (token)
	{
		i = 0;
		new_command = alloc_handling(commands_list_new_node(), program);
		commands_list_add_back(&program->command_list, new_command);
		new_command->command_args = alloc_handling
			(ft_calloc(count_command_args(token) + 1, sizeof(char *)), program);
		while (token && token->type != TOKEN_PIPE)
		{
			if (token->type == TOKEN_WORD && token->previous
				&& (token->previous->type >= 1 && token->previous->type <= 4))
				parse_redirections(token, new_command, program);
			else if (token->type == TOKEN_WORD)
				new_command->command_args[i++] = alloc_handling
					(ft_strdup(token->content), program);
			token = token->next;
		}
		if (token)
			token = token->next;
	}
}
