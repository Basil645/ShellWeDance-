#include "../minishell.h"

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

char	*remove_quotes_from_token(struct s_program_info *program,
		struct s_tokens *token)
{
	char	*new_content;
	char	flag;
	int		i;
	int		j;

	flag = 0;
	i = 0;
	j = 0;
	new_content = alloc_handling
		(ft_calloc(ft_strlen(token->content) + 1, 1), program);
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
	char				*new_content;
	char				*tmp;

	token = program->tokens_list;
	while (token)
	{
		if (((token->previous && token->previous->type != TOKEN_HEREDOC)
				|| (!token->previous)) && token->type == TOKEN_WORD)
		{
			tmp = token->content;
			token->content = remove_quotes_from_token(program, token);
			free(tmp);
		}
		token = token->next;
	}
}
