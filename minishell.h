#include <unistd.h>
#include <stdio.h> // delete
#include "libft.h"
#include <stdlib.h>

struct s_env {
        char    *content;
        struct s_env       *next;
};

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

struct s_replacement_info {
        char    *original;
        char    *prefix;
        char    *value;
};

struct s_expander_info {
	char	*original_str;
	char	*var_name;
	char	*expanded_str;
	int		original_len;
};

enum e_redirection_type {
          INFILE,
          OUTFILE_TRUNCATE,
          OUTFILE_APPEND
};

struct s_redirections_files {
        char    *name;
        enum e_redirection_type type;
        struct s_redirections_files *next;
};

struct s_commands {
        char    *absolute_path;
        char    **command_args;
        int heredoc_fd;
        struct s_redirections_files *files_list;
        struct s_commands *next;
};

struct s_program_info {
	struct s_tokens	*tokens_list;
	struct s_env	*env_list;
	struct s_expander_info	*expander;
	struct s_replacement_info	*rep;
	struct s_commands	*command_list;
};

void    print_tokens(struct s_tokens *list); // delete
struct s_tokens *tokens_list_new_node(char *value);
void    tokens_list_add_back(struct s_tokens **lst, struct s_tokens *new);
void    tokens_list_destroy(struct s_tokens *tokens_list);

struct s_env    *env_list_new_node(char *value);
void    env_list_add_back(struct s_env **lst, struct s_env *new);
char    *get_env_var_value(char *var_name, struct s_env *env_list);
void	env_list_destroy(struct s_env *env_list);
void    get_env_list(struct s_env **env_list, char **envp);

char    *get_expanded_string(struct s_program_info *program, char **str);
void    initialize_expander_info(struct s_program_info *program, char *str);
void    destroy_expander_info(struct s_expander_info *expander);
void	destroy_replacement_info(struct s_replacement_info *rep);
void    destroy_program_info(struct s_program_info *program);

void	*alloc_handling(void *ptr, struct s_program_info *program);

void    files_list_add_back(struct s_redirections_files **lst, struct s_redirections_files *new);
struct s_redirections_files     *files_list_new_node(char *file_name, enum e_redirection_type type);

void    commands_list_add_back(struct s_commands **lst, struct s_commands *new);

void    files_list_destroy(struct s_redirections_files *files_list);

void    assign_tokens_types(struct s_tokens **tokens_list);
void    assign_tokens_content(struct s_program_info *program, char *str);
void    expand_tokens(struct s_program_info *program);
void    split_unquoted_expansion(struct s_program_info *program);
void    remove_empty_tokens(struct s_tokens **tokens_list);
void    remove_quotes_from_tokens(struct s_program_info *program);
void    check_syntax_errors(struct s_tokens *tokens_list);
int     check_unclosed_quotes(char *str);
