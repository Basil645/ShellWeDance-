#include "minishell.h"

struct s_redirections_files	*files_list_new_node(char *file_name, enum e_redirection_type type)
{
	struct s_redirections_files	*node;

	node = malloc(sizeof(struct s_redirections_files));
	if (!node)
		return (NULL);
	node->name = file_name;
	node->next = NULL;
	node->type = type;
	return (node);
}

struct s_redirections_files	*files_list_last_node(struct s_redirections_files *lst)
{
        if (!lst)
                return (NULL);
        while (lst->next != NULL)
                lst = lst->next;
        return (lst);
}

void	files_list_add_back(struct s_redirections_files **lst, struct s_redirections_files *new)
{
	struct s_redirections_files	*lastnode;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	lastnode = files_list_last_node(*lst);
	lastnode->next = new;
}

void	files_list_destroy(struct s_redirections_files *files_list)
{
	struct s_redirections_files	*tmp;

	while (files_list)
	{
		tmp = files_list;
		files_list = files_list->next;
		free(tmp->name);
		free(tmp);
	}
}
