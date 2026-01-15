#include "../minishell.h"

const char *token_type_to_string(enum e_token_type type) // delete
{
    switch (type)
    {
        case TOKEN_WORD:           return "TOKEN_WORD";
        case TOKEN_REDIR_OUTPUT:   return "TOKEN_REDIR_OUTPUT";
        case TOKEN_REDIR_APPEND:   return "TOKEN_REDIR_APPEND";
        case TOKEN_REDIR_INPUT:    return "TOKEN_REDIR_INPUT";
        case TOKEN_HEREDOC:        return "TOKEN_HEREDOC";
        case TOKEN_PIPE:           return "TOKEN_PIPE";
        default:                   return "UNKNOWN_TOKEN";
    }
}

void print_tokens(struct s_tokens *list) // delete
{
    int i = 0;

    printf("\nTokens:\n");

    while (list)
    {
        printf("{[%d] %-10s  \"%s\"}",
               i,
               token_type_to_string(list->type),
               list->content ? list->content : "NULL");

        if (list->next)
            printf("  ->  ");

        list = list->next;
        i++;
    }
    printf("\n");
}

struct s_tokens	*tokens_list_new_node(char *value)
{
	struct s_tokens	*node;	

	node = malloc(sizeof(struct s_tokens));
	if (!node)
		return (NULL);
	node->content = value;
	node->next = NULL;
	node->previous = NULL;
	node->type = -1;
	return (node);
}

struct s_tokens	*tokens_list_last_node(struct s_tokens *lst)
{
        if (!lst)
                return (NULL);
        while (lst->next != NULL)
                lst = lst->next;
        return (lst);
}

void	tokens_list_add_back(struct s_tokens **lst, struct s_tokens *new)
{
	struct s_tokens	*lastnode;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	lastnode = tokens_list_last_node(*lst);
	lastnode->next = new;
	new->previous = lastnode;
}