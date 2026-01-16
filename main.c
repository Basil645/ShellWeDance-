#include "minishell.h"

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
	check_syntax_errors(program->tokens_list, program);// sheet
	get_env_list(&program->env_list, env, program);

        expand_tokens(program);
        split_unquoted_expansion(program);
        remove_empty_tokens(&program->tokens_list);
        remove_quotes_from_tokens(program);
        print_tokens(program->tokens_list);

	// if (!program->tokens_list) // if the list was empty not sure
	// 	return ;
	//program->command_list = ft_calloc(1, sizeof(struct s_commands));
	parser(program);
	print_commands(program->command_list);

	destroy_program_info(program);
        printf("\n\n\n");
}


int main(int argc, char **argv, char **envp)
{
        env = envp;
//test(" >test9 ls<test $s<test2<test>>test4>test5 hello\"-l\"myname   ''is''basil");
        test("cat << end");
    //===== SYNTAX ERRORS ===== 
    //   (exit status -> 2)
    /*test("\'");
    test("\"\"\"");
    test("||||");
    test(">>|><");
    test("cat <<");
    test("cat >> > >> << >>");
    test("> pwd (ls)");
    test("cat | ls > outfile >");
    test("echo hola <<<<< bonjour");
    test("|");
    test("ls | ls < |");
    test("ls >> > file");
    test("||");
    test("<>");
    test("< >ls");
    test("ls | <");
    test("< | <");
    test("<");
    test(">");
    test(">>");
    test("<<");
    test(">>                            >                   >                                   >");*/

	//===== HEREDOC ======
	//test("cat << end < infile"); // no need to save the heredoc input data
	//test("cat << end"); // expands
	//test("cat << \"hello\""); // doesnt expand
	//test("cat << a\'b\'c");
	//test("cat << end");
	//test(" << end | << hello << nani << end1| crazy < eof << eof | ls < eof << i");
	//test("grep < infile << end");
	//test("cat << \"e\"nd");
	//test("<< 1 << 2 << 3");
	//test("<< $");


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
        test("|");
        test("ls | ls");
        test("ls|<outfile");
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
	test("cat<test1<test2<test3>test11>test15>test16");*/
	//test("cat < in1 < in2 < in3 | grep \"error\" < in4 | sort < in5 < in6 | uniq -c | awk '{print $2}' < in7 | tr a-z A-Z | sed 's/FOO/BAR/g' < in8 < in9 | wc -l>out1>out2>out3");
	//test("cat -e < infile -e |ls >outfile -l ");
	//test("\"ls -l\"");
	//test("l\'s\'");
	//test("ls -l <infile>outfile | cat | cat $s");
	//test(" $t\"hell\"jklasfj$t\'jkls fjsdkl fj\'$t"); // t=" ls  -l    -a  "
}