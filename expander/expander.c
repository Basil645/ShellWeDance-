#include "../minishell.h"

char	*replace_var_name_with_value(struct s_program_info *program, 
				char *str, int *i, int j)
{
	char	*tmp;
	char	*new_string;

	program->rep = alloc_handling(ft_calloc(1, sizeof(struct s_replacement_info))
			, program);
	initialize_replacement_info(program, str, *i - j - 1);
	tmp = program->rep->prefix;
	program->rep->prefix = alloc_handling(ft_strjoin(
				program->rep->prefix, program->rep->value), program);
	free(tmp);
	tmp = program->rep->original;
	program->rep->original = alloc_handling(ft_substr(str, *i,
					ft_strlen(str) - *i), program);
	free(tmp);
	tmp = program->rep->original;
	program->rep->original = alloc_handling(ft_strjoin(program->rep->prefix,
				program->rep->original), program);
	*i = *i + ft_strlen(program->rep->value) - j - 2;
	free(tmp);
	tmp = alloc_handling(ft_strdup(program->rep->original), program);
	destroy_replacement_info(program->rep);
	program->rep = NULL;
	return (tmp);
}

void	get_var_name(char *str, char **var_name, int *i, int *j)
{
	*j = 0;
	while (ft_isalpha(str[*i]) || ft_isdigit(str[*i]) || str[*i] == '_')
		(*var_name)[(*j)++] = str[(*i)++];
	(*var_name)[*j] = '\0';
}

char	*get_expanded_string(struct s_program_info *program,
		char **str, int ignore_single_quotes)
{
	int	i;
	int	j;
	char	*tmp;
	int	inside_double_quotes;

	i = 0;
	inside_double_quotes = 0;
	while ((*str)[i])
	{
		ft_memset(program->expander->var_name, 0,
			program->expander->original_len + 1);
		if ((*str)[i] == '\'' && !inside_double_quotes && ignore_single_quotes == 0)
			i = ft_strchr(*str + i + 1, '\'') - *str;
		else if ((*str)[i] == '$')
		{
			// new function -> determine expansion method
			i++;
			if (!ft_isalpha((*str)[i]) && !((*str)[i] == '_'))
				continue ;
			get_var_name(*str, &program->expander->var_name, &i, &j);
			tmp = *str;
			*str = replace_var_name_with_value(program, *str, &i, j);
			free(tmp);
		}
		else if ((*str)[i] == '\"')
			inside_double_quotes = !inside_double_quotes;
		i++;
	}
	return (ft_strdup(*str));
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
			initialize_expander_info(program, token->content, 0);
			tmp = token->content;
			token->content = alloc_handling(ft_strdup(program->expander->expanded_str)
							, program); //prot
			free(tmp);
			destroy_expander_info(program->expander);
			program->expander = NULL;
		}
		token = token->next;
	}
}