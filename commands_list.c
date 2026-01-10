#include "minishell.h"

/*struct s_commands	*commands_list_new_node(char *value)
{
	struct s_commands	*node;	

	node = malloc(sizeof(struct s_commands));
	if (!node)
		return (NULL);
	node->absolute_path = value;
	node->next = NULL;
	return (node);
}*/

struct s_commands	*commands_list_last_node(struct s_commands *lst)
{
        if (!lst)
                return (NULL);
        while (lst->next != NULL)
                lst = lst->next;
        return (lst);
}

void	commands_list_add_back(struct s_commands **lst, struct s_commands *new)
{
	struct s_commands	*lastnode;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	lastnode = commands_list_last_node(*lst);
	lastnode->next = new;
}

void	free_two_dimensional(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	command_destroy(struct s_commands *command)
{
	if (command->absolute_path)
		free(command->absolute_path);
	if (command->command_args)
		free_two_dimensional(command->command_args);
	if (command->heredoc_fd != -1)
	{
		close(command->heredoc_fd);
		command->heredoc_fd = -1;
	}
	if (command->files_list)
		files_list_destroy(command->files_list);
}

void	commands_list_destroy(struct s_commands *commands_list)
{
	struct s_commands	*tmp;

	while (commands_list)
	{
		tmp = commands_list;
		commands_list = commands_list->next;
		command_destroy(tmp);
	}
}
