#include "minishell.h"

void ft_print_args(char **arguments)
{
	int counter;

	counter = 0;
	while(arguments && arguments[counter])
	{
		printf(YEL"|%s|\n"RESET,arguments[counter]);
		counter++;
	}
	if (arguments[counter] == NULL)
		printf(YEL"|%s|\n"RESET, arguments[counter]);
}

void ft_print_simple_comand(t_simple_command *simple_command)
{
	printf(BLU"-----------------simple_command:---------------------\n"RESET);
	if(simple_command->arguments[0])
		ft_print_args(simple_command->arguments);
	if (simple_command->outfiles[0])
	{
		printf("-------outfiles------\n");
		ft_print_args(simple_command->outfiles);
		printf(GRN"is_cat =%d\n"RESET, simple_command->is_cat);
	}
	if (simple_command->infiles && simple_command->infiles[0])
	{
		printf("-------infiles-------\n");
		ft_print_args(simple_command->infiles);
	}
}

void ft_print_all_command(t_simple_command **command_table)
{
	int i = 0;
	if(command_table == NULL || command_table[0] == NULL)
	{
		printf("empty line\n");
		return ;
	}
	while(command_table[i])
	{
		ft_print_simple_comand(command_table[i]);
		i++;
	}
}

void ft_print_lexer_result(char **lexer_result)
{
	int count;

	count = 0;
	printf("----------------lexer-result-------------------\n");
	while (lexer_result && lexer_result[count])
	{
		printf("[%3d] |%10s|\n", count, lexer_result[count]);
		count++;
	}
	printf("----------------lexer-result-------------------\n");
}

int		get_semicolon_index(char *line)
{
	int		count;
	int		flag_brace_single;
	int		flag_brace_double;
	int		flag_slash;

	count = 0;
	flag_brace_double = 0;
	flag_brace_single = 0;
	flag_slash = 0;
	while (line[count])
	{
		if (line[count] == '\\')
		{
			flag_slash = 1;
			count++;
			continue ;
		}
		if (line[count] == '"' && !flag_brace_single && !flag_slash)
			flag_brace_double = !flag_brace_double;
		if (line[count] == '\'' && !flag_brace_double && !flag_slash)
			flag_brace_single = !flag_brace_single;
		if (line[count] == ';' && !flag_slash && !flag_brace_single && !flag_brace_double)
			break ;
		count++;
		flag_slash = 0;
	}
	return (count);
}

char	*shift_line_2(char *line)
{
	char	*line_p;
	int		semicolon_index;
	int		count;

	count = 0;
	if (NULL == line || '\0' == line[0])
		return (line);
	semicolon_index = get_semicolon_index(line);
	if (line[semicolon_index] == ';')
		semicolon_index++;
	line_p = &line[semicolon_index];
	while (line_p[count])
	{
		line[count] = line_p[count];
		count++;
	}
	line[count] = '\0';
	return (line);
}

void	free_lexer_results(char ***lexer_results)
{
	int count;

	count = 0;
	while ((*lexer_results)[count])
	{
		free((*lexer_results)[count]);
		count++;
	}
	free((*lexer_results)[count]);
	free(*lexer_results);
	*lexer_results = NULL;
}

void	free_argument_list(char ***list)
{
	int	count;

	count = 0;
	while ((*list)[count])
	{
		free((*list)[count]);
		count++;
	}
	free((*list)[count]);
	free(*list);
	*list = NULL;
}

void	free_simple_command(t_simple_command *simple_command)
{
	free_argument_list(&simple_command->arguments);
	free_argument_list(&simple_command->outfiles);
	free_argument_list(&simple_command->infiles);
	free(simple_command->outfiles);
	free(simple_command->infiles);
	free(simple_command->arguments);
}

void	free_command_table(t_common *common)
{
	t_simple_command	**command_table;
	int					count;

	count = 0;
	command_table = common->command.simple_commands;
	while (command_table[count])
	{
		free_simple_command(command_table[count]);
		free(command_table[count]);
		count++;
	}
	free(command_table[count]);
	free(common->command.simple_commands);
}

void ft_do_command(t_common *common)
{
	char		**lexer_result;
	int 		gnl_rv;

	if (common->termcap->line[0] == '\0') //line == NULL ||
	{
		prompt();
		gnl_rv = t_get_next_line(&common->termcap->line, common->termcap);
		to_cannon();

		if ((common->termcap->line[0] == 0) && 1 == gnl_rv) // line == NULL ||
			mini_exit(common);
//		ft_hello(common->termcap->line);		//ft_hello :)
		if (syntax_error(common->termcap->line))
		{
			common->termcap->line[0] = '\0';
			return ;
		}
		write(1, "\n", 1);											//печатает пустую строку, без него не переходит
//		printf("-----------------------------line from gnl - |%s|\n", line);
	}
	if (NULL == (lexer_result = lexer(common->termcap->line, common)))
	{
		shift_line_2(common->termcap->line); //line =
		return ;
	}
	if (invalid_lexer_result(lexer_result))
	{
		common->termcap->line[0] = '\0';
		return ;
	}
//	ft_print_lexer_result(lexer_result);

	common->command = get_command_table(lexer_result);
//	printf("\n");
//	ft_print_all_command(common->command.simple_commands);
	shift_line_2(common->termcap->line);
	executor(common);
	free_lexer_results(&lexer_result);
	free(lexer_result);
	free_command_table(common);
}

void	minishell_loop(char **envp)
{
	t_common	*common;

	common = common_init((char **)envp);
	signal_processor();
//	g_signal_process_status = 0;
	while (1)
	{
		ft_do_command(common);
	}
}

int main(int argc, char const **argv, char const **envp)
{
	(void)argc;
	(void)argv;
	g_errno = 0;
	setbuf(stdout, NULL);

	minishell_loop((char **)envp);
	return (0);
}