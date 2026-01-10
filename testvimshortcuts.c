#include <stdio.h>
#include "libft.h"
#include <stdlib.h>

enum	e_token_type{
	TOKEN_WORD,
	TOKEN_REDIR_OUTPUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_INPUT,
	TOKEN_HEREDOC,
	TOKEN_PIPE
};

struct	s_tokens {
	char	*content;
	enum	e_token_type type;
	struct s_tokens	*previous;
	struct s_tokens	*next;
};

void	print2d(char **arr)
{
	int i = 0;

	while (arr[i])
	{
		printf("[%s] ", arr[i]);
		i++;
	}
}

void    print_tokens(struct s_tokens *list)
{
	struct s_tokens *temp = list;

        while (temp)
        {
                printf(" [type: %d,%s]->  ", temp->type,temp->content);
                temp = temp->next;
        }
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

void    print_tokens_reverse(struct s_tokens *list)
{
        struct s_tokens *temp = tokens_list_last_node(list);

        while (temp)
        {
                ft_printf(" [type: %d, %s]-> ", temp->type, temp->content);
                temp = temp->previous;
        }
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

int	assign_tokens_content(char *str, struct s_tokens **tokens_list) // so big will be splited into two function one to split redirections and pipes and one for the words
{
	struct s_tokens *new_node;
	int i;
	int x;

	i = 0;
        while (str[i])
        {
                if (str[i] == ' ')
                        i++;
		else
		{
			if (str[i] == '<' || str[i] == '>' || str[i] == '|')
				if (str[i] == str[i + 1] && str[i] != '|')
					new_node = tokens_list_new_node(ft_substr(str, (i+=2) - 2, 2));
				else
					new_node = tokens_list_new_node(ft_substr(str, i++, 1));
                	else
                	{
                       		int j = 0;
                        	while (str[i + j] && !ft_strchr(" <>|", str[i + j]))
                        	{
                                	if (str[i + j] == '\"' || str[i + j] == '\'')
                                	{
                                        	if (!ft_strchr(str + i + j + 1, str[i + j]))
                                                	return (0);
                                        	else
							j += ft_strchr(str + i + j + 1, str[i + j]) - (str + j + i) + 1;
					}
					else
						j++;
				}
				new_node = tokens_list_new_node(ft_substr(str, i, j));
				i += j;
			}
		/*	if (!new_node)
				handle_syserror(-1);*/
			tokens_list_add_back(tokens_list, new_node);
		}
                /*if (!tokens[x - 1])
                        handle_syserror(-1);*/
        }
        return (1);
}

void	handle_tokenizer_error(char *str, int exit_status) // will be implemented soon when handling memory leaks
{
	//free_tokens_list();
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
				handle_tokenizer_error("unexpected input for redirection\n", 2);
			else if (tokens_list->next->type != TOKEN_WORD)
				handle_tokenizer_error("unexpected input for redirection\n", 2);
		}
		else if (tokens_list->type == TOKEN_PIPE)
		{
			if (!tokens_list->next || !tokens_list->previous)
				handle_tokenizer_error("unexpected input for \'|\'\n", 2);
			else if (tokens_list->next->type == TOKEN_PIPE)
				handle_tokenizer_error("unexpected input for \'|\'\n", 2);
		}
		tokens_list = tokens_list->next;
	}
}

void	test(char *str)
{
	static int testnum = 1;
	printf("test %d:\n",testnum);
	printf("%s\n",str);
        struct s_tokens *tokens_list  = NULL;
        assign_tokens_content(str, &tokens_list);
        assign_tokens_types(&tokens_list);
        print_tokens(tokens_list);
	check_syntax_errors(tokens_list);
        printf("\n\n\n");
	testnum++;
}

int main()
{
	test(" >test9 ls<test<test1<test2<>test>test4>test5 hello\"-l\"myname   ''is''basil");
	test(" ls \"-l -a\" <          test1 | cat >outfile");
	test("<<<<<<<<<<<<>test9999");
	test("ls                                   >                                             hello1");
	test("<test11 ls <test1<test13>toast1 -l");
	test("\"\"\'\'echo hola\"\"\'\'\'\' que\"\"\'\' tal\"\"\'\'");
	test("\"\"\'\'\"echo hola\"\"\"\'\'\'\' que\"\"\'\' tal\"\"\'\'");
	test("cat \" \\\" \""); // fail
	test("echo \"hello\"\""); //fail
	test("\"\'$a\'\"");
	test("\"\'hello\"");
	test("");
	test("<");
	test(">");
	test("<<");
	test(">>");
	test(">>                            >                   >                                   >");
	test("|");
	test("ls | ls");
	test("ls|<outfile");
	test("||||");
	test(">>|><");
	test("echo hola <<<<< bonjour");
	test("cat <<");
	test("cat >> > >> << >>");
	test("> pwd (ls)");
	test("cat | ls > outfile >");
	test(" echo hola > a >>b echo que tal cat a | <b cat | cat > c | cat");
	test("ls | | | wc");
	test("ls |");
	test("<>");
	test("echo \">\"");
	test("echo hello > | wc");
	test("cat < | grep hi");
	test("     &&&&&       ");
	test("echo oui | echo non | echo hola | grep hola");
}
