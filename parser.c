#include "minishell.h"

const char *redir_type_to_str(enum e_redirection_type type) // delete
{
    if (type == INFILE)
        return ("INFILE");
    if (type == OUTFILE_TRUNCATE)
        return ("OUTFILE_TRUNCATE");
    if (type == OUTFILE_APPEND)
        return ("OUTFILE_APPEND");
    return ("UNKNOWN");
}


void print_args(char **args)//delete
{
    int i;

    if (!args)
    {
        printf("  Args         : (none)\n");
        return;
    }

    printf("  Args         :\n");
    i = 0;
    while (args[i])
    {
        printf("    [%d] %s\n", i, args[i]);
        i++;
    }
}

void print_redirections(struct s_redirections_files *files)//delete
{
    if (!files)
    {
        printf("  Redirections : (none)\n");
        return;
    }

    printf("  Redirections :\n");
    while (files)
    {
        printf("    -> %-18s : %s\n",
               redir_type_to_str(files->type),
               files->name);
        files = files->next;
    }
}

void    read_heredoc_test(int fd) // delete
{
        char buffer[1];

        while (read(fd, buffer, 1))
        {
                printf("%c", buffer[0]);
        }
}


void print_commands(struct s_commands *cmds)//delete
{
    int i;

    i = 1;
    while (cmds)
    {
        printf("\n================ COMMAND %d ================\n", i);
//        printf("  Path         : %s\n",
//             cmds->absolute_path ? cmds->absolute_path : "(null)");
        print_args(cmds->command_args);
        printf("  Heredoc FD   : %d\n", cmds->heredoc_fd);
	printf("  Heredoc DATA :\n");
	if (cmds->heredoc_fd != -1)
	read_heredoc_test(cmds->heredoc_fd);
        print_redirections(cmds->files_list);
        printf("===========================================\n");

        cmds = cmds->next;
        i++;
    }
}

int	count_command_args(struct s_tokens *token)
{
	int	count;

	count = 0;
	while (token && token->type != TOKEN_PIPE)
	{
		if (token->type == TOKEN_WORD)
			if (!token->previous || token->previous->type == TOKEN_WORD
					|| token->previous->type == TOKEN_PIPE)
				count++;
		token = token->next;
	}
	return (count);
}

int	get_file_type(enum e_token_type type)
{
	if (type == TOKEN_REDIR_OUTPUT)
		return (OUTFILE_TRUNCATE);
	if (type == TOKEN_REDIR_APPEND)
		return (OUTFILE_APPEND);
	if (type == TOKEN_REDIR_INPUT)
		return (INFILE);
	return (-1);
}

int	heredoc_is_infile(struct s_tokens *token)
{
	int	is_infile;

	is_infile = 1;
	while (token && token->type != TOKEN_PIPE)
	{
		if (token->type == TOKEN_HEREDOC || token->type == TOKEN_REDIR_INPUT)
		{
			is_infile = 0;
			break ;
		}
		token = token->next;
	}
	return (is_infile);
}

void	read_heredoc_not_infile(char *limiter, struct s_program_info *program)
{
	char	*line;

	line = NULL;
	while (!line || ((ft_strlen(line) - 1) != ft_strlen(limiter)
			|| ft_strncmp(line, limiter, ft_strlen(limiter))))
	{
		if (line)
			free(line);
		ft_printf(">");
		line = alloc_handling(get_next_line(0), program); // prot
	}
	free(line);
}

int	read_heredoc_infile(char *limiter, struct s_program_info *program, int expand_heredoc_content)
{
	char	*line;
	int		fd[2];

	handle_syserror(pipe(fd), program);
	line = NULL;
	while (!line || ((ft_strlen(line) - 1) != ft_strlen(limiter)
			|| ft_strncmp(line, limiter, ft_strlen(limiter))))
	{
		if (line)
			free(line);
		ft_printf(">");
		line = get_next_line(0); // prot
		if (!line)
		{
			close(fd[0]);
			close(fd[1]);
			alloc_handling(NULL, program);
		}
		if ((ft_strlen(line) - 1) != ft_strlen(limiter)
				|| ft_strncmp(line, limiter, ft_strlen(limiter)))
		{
			if (expand_heredoc_content)
			{
				program->expander = alloc_handling(ft_calloc
						(sizeof(struct s_expander_info), 1), program); // free line
				char *tmp = line;
				initialize_expander_info(program, line, 1);
				line = alloc_handling(ft_strdup(program->expander->expanded_str), program); // stupid prot you should free (line)
				free(tmp);
				destroy_expander_info(program->expander);
				program->expander = NULL;
			}
			write(fd[1], line, ft_strlen(line));
		}
	}
	free(line);
	close(fd[1]);
	return (fd[0]);
}

void	parse_heredoc(struct s_tokens *token, struct s_commands *new_command,
		struct s_program_info *program)
{
	int	expand_heredoc_content;
	char	*tmp;

	expand_heredoc_content = !(ft_strchr(token->content, '\'') || 
					ft_strchr(token->content, '\"'));
	tmp = token->content;
	token->content = remove_quotes_from_token(program, token);
	free(tmp);
	if (heredoc_is_infile(token))
		new_command->heredoc_fd = read_heredoc_infile(token->content, program,
						expand_heredoc_content);
	else
		read_heredoc_not_infile(token->content, program);
}

void	parse_redirections(struct s_tokens *token, struct s_commands *new_command,
			struct s_program_info *program)
{
	struct s_redirections_files     *new_file;
	char	*file_name;
	int	file_type;

	if (token->previous->type >= TOKEN_REDIR_OUTPUT &&
			token->previous->type <= TOKEN_REDIR_INPUT)
	{
			file_type = get_file_type(token->previous->type);
			file_name = alloc_handling(ft_strdup(token->content), program); // prot free new_command
			new_file = files_list_new_node(file_name, file_type); // prot free new_command
			if (!new_file)
			{
				free(file_name);
				alloc_handling(NULL, program);
			}
			files_list_add_back(&new_command->files_list, new_file);
	}
	else if (token->previous->type == TOKEN_HEREDOC)
		parse_heredoc(token, new_command, program);
}

void	parser(struct s_program_info *program)
{
	struct s_tokens	*token;
	struct s_commands	*new_command;
	int	i;

	token = program->tokens_list;
	while (token)
	{
		i = 0;
		new_command = alloc_handling(ft_calloc(1, sizeof(struct s_commands)), program);
        	new_command->heredoc_fd = -1;
		new_command->command_args = alloc_handling(ft_calloc(count_command_args(token) + 1, sizeof(char *)), program);
		while (token && token->type != TOKEN_PIPE)
		{
			if (token->type == TOKEN_WORD && token->previous && (token->previous->type
						>= TOKEN_REDIR_OUTPUT && token->previous->type <= TOKEN_HEREDOC))
					parse_redirections(token, new_command, program);
			else if (token->type == TOKEN_WORD)
				new_command->command_args[i++] = alloc_handling(ft_strdup(token->content), program);
			token = token->next;
		}
		commands_list_add_back(&program->command_list, new_command);
		if (token)
			token = token->next;
	}
}

char **env;

void	test(char *str)
{
	static int testnum = 1;
	printf("test %d:\n",testnum++);
	printf("%s\n",str);
	if (!check_unclosed_quotes(str))
	{
		printf("unclosed quotes\n");
		return ;
	}
	struct s_program_info *program;
	program = malloc(sizeof(struct s_program_info)); // prot
	ft_memset(program, 0 , sizeof(struct s_program_info));
	assign_tokens_content(program, str);
        assign_tokens_types(&program->tokens_list);
	check_syntax_errors(program->tokens_list);// sheet
	get_env_list(&program->env_list, env);

        expand_tokens(program);
        split_unquoted_expansion(program);
        remove_empty_tokens(&program->tokens_list);
        remove_quotes_from_tokens(program);
        print_tokens(program->tokens_list);

	if (!program->tokens_list) // if the list was empty not sure
		return ;
	//program->command_list = ft_calloc(1, sizeof(struct s_commands));
	parser(program);
	print_commands(program->command_list);

	destroy_program_info(program);
        printf("\n\n\n");
}


int main(int argc, char **argv, char **envp)
{
        env = envp;
	//===== HEREDOC ======
	//test("cat << end < infile"); // no need to save the heredoc input data
	//test("cat << end"); // expands
	//test("cat << \"hello\""); // doesnt expand
	//test("cat << a\'b\'c");
	test("cat << end");
	//test(" << end | << hello << nani << end1| crazy < eof << eof | ls < eof << i");
	//test("grep < infile << end");
	
        /*test("echo $USERs");
        test("$$$$$$$$$");
        test("echo \"$USER\"");
        test("echo \'$USER\'");
        test("echo $PWD\"$USER\"\'$HOME\'");
        test("echo \"$NON $PWD\"");
        test("$non_exist $SHELL");// should we change this value to nothing?
        test("safsf    \"fsdfa     <$jfds>$HOME\"");
        test("fffff \'cake   \' cd -l");
        test(" $test ");
        test(" $a5 ");
        test("$5a "); //
        test("echo $\"HOM\"E"); //
        test("echo $HOME\"HOME\"");
        test("echo $\'$\'$\'$\'"); //
        test("echo \"$USER\"\'$HOME\'\"$VAR\"");
        test(" $UNDEF "); // export =""
        test(" echo $0$1230$0 ");
        test("echo $dfsfds");
        test("echo $test $test $test abcd $non_exist $test 123 $test"); //  test=\"            \"
        test("cat << \'$HOME\' << \"$HOME\" << $HOME");
        test("vim \"\"");
        test("ls \"\""); // different than ls
        test(" >test9 ls<test<test1<test2<>test>test4>test5 hello\"-l\"myname   ''is''basil");
        test(" ls \"-l -a\" <          test1 | cat >outfile");
        test("<<<<<<<<<<<<>test9999");
        test(" echo $HOME $PWD $EMPTY \"$USER\" \'  $TEST  \' << $HOME > $HOME > '$HOME' ");
        test("ls $t");
        test("$t");
        test("ls                                   >                                             hello1");
        test("<test11 ls <test1<test13>toast1 -l");
        test("\"\"\'\'echo hola\"\"\'\'\'\' que\"\"\'\' tal\"\"\'\'");
        test("\"\"\'\'\"echo hola\"\"\"\'\'\'\' que\"\"\'\' tal\"\"\'\'");
        test("cat \" \\\" \""); // fail -> unclosed quotes
        test("echo \"hello\"\""); //fail -> unclose quotes
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
        test("  \"  yaman's book  \"   ");
        test("echo $HOME");
        test("echo \'$HOME\'");
        test("echo \"$HOME\"");
        test("cat \'ft\'\"_\"split.\'c\'  ");
        test("  echo        \'$\'HOME\'\'\'\' \"\"    ");
        test("  echo        \"$\"HOME\'\'\'\' \"\"    ");
        test("  $HOME \'$HOME\' \"$HOME\"  ");
        test(" \"  \'   \" ");
        test(" echo $HOME $PWD $EMPTY \"$USER\" \'  $TEST  \' << $HOME > $HOME > '$HOME' ");
        test(" $HOME     \" $t \"  ");
        test(" echo \"$t\"\"a\" "); // t="ls        -l"
        test(" echo $t\"a\" ");
        test(" echo my shit terminal is [$TERM] ");
        test(" user id: $UID"); // fail
        test(" echo $HOME9 ");
        test(" echo $9HOME");
        test(" echo $USER$var\\$USER$USER\\$USERtest$USER ");
        test(" echo $hola* ");
        test(" echo $hola/ ");
        test(" \"\"e\"\'c\'ho \'b\'\"o\"nj\"o\"\'u\'r\" ");
        test(" \"e\"\'c\'ho \'b\'\"o\"nj\"o\"\'u\'r ");
        test(" >> << \" >> << ");
        test(" echo $t"); // t=" ls   -l  -a  < > >> | "
        test(" \"<<\" ");
        test(" echo  \"basil\'s home is  $HOME  \" and \'$HOME\' doesnt expand  \'te\"st\'  ");
        test("echo hola\'\"\"\"\"\"\"\"\"\"\"\'");
        test("echo hola\"\"\"\"\"\"\"\"\"\"");
        test("?$HOME");
        test(" e\'cho hola\'");
        test(" echo \"$HOME\"HOME");
        test("echo  \"\'\'h\'o\'la\'\'\"");
        test(" echo      << hello\"$HOME\" ");
        test("");
        test("                             ");
        test("$x$y$z $xyz");
        test("$x$y$z");
        test("hello");
        test("$doesnotexist?");
        test("\'$HOMEdskjhfkdshfsd\'");
        test("$");
	test("ls |grep foo|wc -l");
	test("cat<test1<test2<test3>test11>test15>test16");
	test("cat < in1 < in2 < in3 | grep \"error\" < in4 | sort < in5 < in6 | uniq -c | awk '{print $2}' < in7 | tr a-z A-Z | sed 's/FOO/BAR/g' < in8 < in9 | wc -l>out1>out2>out3");*/
}
