#include "minishell.h"

/*void    print_envs(struct s_env *list)
{
	struct s_env *temp = list;

        while (temp)
        {
                printf("%s\n", temp->content);
                temp = temp->next;
        }
}*/

struct s_env	*env_list_new_node(char *value)
{
	struct s_env	*node;	

	node = malloc(sizeof(struct s_env));
	if (!node)
		return (NULL);
	node->content = value;
	node->next = NULL;
	return (node);
}

struct s_env	*env_list_last_node(struct s_env *lst)
{
        if (!lst)
                return (NULL);
        while (lst->next != NULL)
                lst = lst->next;
        return (lst);
}

void    env_list_add_back(struct s_env **lst, struct s_env *new)
{
        struct s_env *lastnode;

        if (!lst || !new)
                return ;
        if (!*lst)
        {
                *lst = new;
                return ;
        }
        lastnode = env_list_last_node(*lst);
        lastnode->next = new;
}


void	env_list_destroy(struct s_env *env_list)
{
	struct s_env	*tmp;

	while (env_list)
	{
		tmp = env_list;
		env_list = env_list->next;
		free(tmp);
	}
}

void    get_env_list(struct s_env **env_list, char **envp)
{
        int     i;
        struct s_env *new_node;

        i = 0;
        while (envp[i++])
        {
                new_node = env_list_new_node(envp[i - 1]);
                /*if (!new_node)
                        handle_syserror();*/
                env_list_add_back(env_list, new_node);
        }
}

char	*get_env_var_value(char *var_name, struct s_env *env_list)
{
	int	var_name_length;

	var_name_length = ft_strlen(var_name);
	while (env_list)
	{
		if (ft_strlen(env_list->content) >= var_name_length)
			if (!ft_strncmp(env_list->content, var_name, var_name_length)
					&& env_list->content[var_name_length] == '=')
				return (ft_strdup(&env_list->content[var_name_length + 1]));
		env_list = env_list->next;
	}
	return (ft_strdup(""));
}
