#include "minishell.h"

void	assign_tokens_types(struct s_tokens **tokens_list)
{
	struct s_tokens	*tmp;

	tmp = *tokens_list;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, "|",1) && ft_strlen(tmp->content) == 1)
			tmp->type = TOKEN_PIPE;
		else if (!ft_strncmp(tmp->content, "<",1) && ft_strlen(tmp->content) == 1)
			tmp->type = TOKEN_REDIR_INPUT;
		else if (!ft_strncmp(tmp->content, ">",1) && ft_strlen(tmp->content) == 1)
                        tmp->type = TOKEN_REDIR_OUTPUT;
		else if (!ft_strncmp(tmp->content, ">>",2) && ft_strlen(tmp->content) == 2)
                        tmp->type = TOKEN_REDIR_APPEND;
		else if (!ft_strncmp(tmp->content, "<<",2) && ft_strlen(tmp->content) == 2)
                        tmp->type = TOKEN_HEREDOC;
		else
			tmp->type = TOKEN_WORD;
		tmp = tmp->next;
	}
}

void	assign_tokens_words(struct s_program_info *program, int *i, char *str, struct s_tokens **new_node)
{
	int		j;
	char	*content;

	j = 0;
	while (str[*i + j] && !ft_strchr(" <>|", str[*i + j]))
	{
		if (str[*i + j] == '\"' || str[*i + j] == '\'')
			j += ft_strchr(str + *i + j + 1, str[*i + j]) - (str + j + *i) + 1;
		else
			j++;
	}
	content = alloc_handling(ft_substr(str, *i, j), program);
	*new_node = tokens_list_new_node(content);//two protections
	if (!(*new_node))
	{
		free(content);
		alloc_handling(NULL, program);
	}
	*i += j;
}

void	assign_tokens_redirections_pipes(struct s_program_info *program, int *i, char *str, struct s_tokens **new_node)
{	
	char	*content;

	if (str[*i] == str[*i + 1] && str[*i] != '|')
	{
		content = alloc_handling(ft_substr(str, *i, 2), program);
		*new_node = tokens_list_new_node(content); // prot
		(*i) += 2;
	}
	else
	{
		content = alloc_handling(ft_substr(str, *i, 1), program);
		*new_node = tokens_list_new_node(content); // prot
		(*i)++;
	}
	if (!(*new_node))
	{
		free(content);
		alloc_handling(NULL, program);
	}
}

void	assign_tokens_content(struct s_program_info *program, char *str)
{
	struct s_tokens *new_node;
	int			i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		else
		{
			if (str[i] == '<' || str[i] == '>' || str[i] == '|')
				assign_tokens_redirections_pipes(program, &i, str, &new_node);
			else
				assign_tokens_words(program, &i, str, &new_node);
			tokens_list_add_back(&program->tokens_list, new_node);
		}
	}
}

void	expand_tokens(struct s_program_info *program)
{
	char	*tmp;
	struct s_tokens *token;

	token = program->tokens_list;
	while (token)
	{
		if (((token->previous && token->previous->type != TOKEN_HEREDOC)
					|| (!token->previous)) && token->type == TOKEN_WORD)
		{
			program->expander = alloc_handling(ft_calloc
						(sizeof(struct s_expander_info), 1), program); // prot
			initialize_expander_info(program, token->content);
			tmp = token->content;
			token->content = alloc_handling(ft_strdup(program->expander->expanded_str)
							, program); //prot
			if (tmp)
			free(tmp);
			destroy_expander_info(program->expander);
			program->expander = NULL;
		}
		token = token->next;
	}
}

void	insert_expanded_token_before(struct s_program_info *program,
			struct s_tokens *token, struct s_tokens *new_token)
{
	if (token->previous)
		token->previous->next = new_token;
	new_token->next = token;
	new_token->type = TOKEN_WORD;
	if (token->previous)
		new_token->previous = token->previous;
	else
	{
		new_token->previous = NULL;
		program->tokens_list = new_token;
	}
	token->previous = new_token;
}

void	split_by_spaces(struct s_program_info *program, struct s_tokens *token, int i) // NULL checks
{
	int			j;
	char		*tmp;
	struct s_tokens	*new_token;

	j = 0;
	while (token->content[i + j] == ' ')
		j++;
	tmp = alloc_handling(ft_substr(token->content, 0, i), program);
	new_token = tokens_list_new_node(tmp); // 2 protection
	if (!new_token)
	{
		free(tmp);
		alloc_handling(NULL, program);
	}
	i += j;
	tmp = token->content;
	token->content = ft_substr(token->content, i, ft_strlen(token->content) - i);// protection
	free(tmp);
	if (!token->content)
	{
		free(new_token->content);
		free(new_token);
		alloc_handling(NULL, program);
	}
	insert_expanded_token_before(program, token, new_token);
}


void    split_unquoted_expansion(struct s_program_info *program)
{
	int	i;
	struct s_tokens	*token;

	token = program->tokens_list;
	while (token)
	{
		if (((token->previous && token->previous->type != TOKEN_HEREDOC)
					|| (!token->previous)) && token->type == TOKEN_WORD)
		{
			i = 0;
			while (token->content[i])
			{
				if (token->content[i] == '\'' || token->content[i] == '\"')
					i = ft_strchr(token->content + i + 1, token->content[i]) - token->content + 1;
				else if (token->content[i] == ' ')
				{
					split_by_spaces(program, token, i);
					i = 0;
				}
				else
					i++;
			}
		}
		token = token->next;
	}
}

void	remove_empty_tokens(struct s_tokens **tokens_list)
{
	struct s_tokens	*token;
	struct s_tokens	*tmp;

	token = *tokens_list;
	while (token)
	{
		if (!ft_strlen(token->content))
		{
			tmp = token;
			if (token->previous)
				token->previous->next = token->next;
			else
				*tokens_list = token->next;
			if (token->next)
				token->next->previous = token->previous;
			token = token->next;
			free(tmp->content);
			free(tmp);
		}
		else
			token = token->next;
	}
}

char	*remove_quotes_from_token(struct s_program_info *program, struct s_tokens *token)
{
	char	*new_content;// prot
	char	flag;
	int		i;
	int		j;

	flag = 0;
	i = 0;
	j = 0;
	new_content = alloc_handling(ft_calloc(ft_strlen(token->content) + 1, 1), program);
	while (token->content[i])
	{
		if (!flag && (token->content[i] == '\'' || token->content[i] == '\"'))
			flag = token->content[i];
		else if (flag && token->content[i] == flag)
			flag = 0;
		else if (token->content[i] != flag)
			new_content[j++] = token->content[i];
		i++;
	}
	new_content[j] = '\0';
	return (new_content);
}

void	remove_quotes_from_tokens(struct s_program_info *program)
{
	struct s_tokens		*token;
	char			*new_content;
	char			*tmp;

	token = program->tokens_list;
	while (token)
	{
		if (((token->previous && token->previous->type != TOKEN_HEREDOC)
		  		|| (!token->previous)) && token->type == TOKEN_WORD)
		{
			tmp = token->content;
			token->content = remove_quotes_from_token(program, token); // prot
			free(tmp);
		}
		token = token->next;
	}
}

void	destroy_program_info(struct s_program_info *program)
{
	if (program->tokens_list)
		tokens_list_destroy(program->tokens_list);
	if (program->env_list)
		env_list_destroy(program->env_list);
	if (program->expander)
		destroy_expander_info(program->expander);
	if (program->rep)
		destroy_replacement_info(program->rep);
	free(program);
}

void	handle_error(char *str, int exit_status) // will be implemented soon when handling memory leaks
{
	ft_printf("%s", str);
	//exit(exit_status);
}

void	check_syntax_errors(struct s_tokens *tokens_list) // a testing function not the final version
{
	while (tokens_list)
	{
		if (tokens_list->type != TOKEN_WORD && tokens_list->type != TOKEN_PIPE)
		{
			if (!tokens_list->next)
				handle_error("unexpected input for redirection\n", 2);
			else if (tokens_list->next->type != TOKEN_WORD)
				handle_error("unexpected input for redirection\n", 2);
		}
		else if (tokens_list->type == TOKEN_PIPE)
		{
			if (!tokens_list->next || !tokens_list->previous)
				handle_error("unexpected input for \'|\'\n", 2);
			else if (tokens_list->next->type == TOKEN_PIPE)
				handle_error("unexpected input for \'|\'\n", 2);
		}
		tokens_list = tokens_list->next;
	}
}

int	check_unclosed_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (!ft_strchr(str + i + 1, str[i]))
				return (0);
			i = ft_strchr(str + i + 1, str[i]) - str + 1;
		}
		else
			i++;
	}
	return (1);
}
