#include "../minishell.h"

void	initialize_replacement_info(struct s_program_info *program, char *str, int prefix_len)
{
	program->rep->original = alloc_handling(ft_strdup(str), program);
	program->rep->value = alloc_handling(
			get_env_var_value(program->expander->var_name, program->env_list), program);
	program->rep->prefix = alloc_handling(ft_substr(str, 0, prefix_len), program);
}

void	initialize_expander_info(struct s_program_info *program, char *str,
			int ignore_single_quotes)
{
	program->expander->original_str = alloc_handling(ft_strdup(str), program);
	program->expander->original_len = ft_strlen(str);
	program->expander->var_name = ft_calloc(ft_strlen(str) + 1, 1);
	alloc_handling(program->expander->var_name, program);
	program->expander->expanded_str = get_expanded_string(program,
				&program->expander->original_str, ignore_single_quotes);
}
