#include "../minishell.h"

void	handle_syntax_error(char *str, struct s_program_info *program)
{
	write(2, "-minishell: syntax error near unexpected token `", 48);
	write(2, str, ft_strlen(str));
	write(2, "\'\n", 2);
	destroy_program_info(program);
	exit(2);
}

void	check_syntax_errors(struct s_tokens *tokens_list,
	struct s_program_info *program)
{
	while (tokens_list)
	{
		if (tokens_list->type != TOKEN_WORD && tokens_list->type != TOKEN_PIPE)
		{
			if (!tokens_list->next)
				handle_syntax_error("newline", program);
			else if (tokens_list->next->type != TOKEN_WORD)
				handle_syntax_error(tokens_list->next->content, program);
		}
		else if (tokens_list->type == TOKEN_PIPE)
		{
			if (!tokens_list->next || !tokens_list->previous)
				handle_syntax_error("|", program);
			else if (tokens_list->next->type == TOKEN_PIPE)
				handle_syntax_error("|", program);
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
