#include "minishell.h"

void	*alloc_handling(void *ptr, struct s_program_info *program)
{
	if (!ptr)
	{
		perror("error:");
		destroy_program_info(program);
		exit(EXIT_FAILURE);
	}
	return (ptr);
}
