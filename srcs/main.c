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

char *shift_line(char *line)
{
	int len_to_shift;
	char *new_line;

	new_line = NULL;
	if (line && line[0])
	{
		len_to_shift = ft_strlen_to_char(line, ';');
		if (line[len_to_shift] == '\0')
			return (NULL);
//	printf("-[%d]\n", len_to_shift);
//	printf("=%s\n", line + len_to_shift + 1);
		if (line + len_to_shift + 1)
			new_line = line + len_to_shift + 1;
	}
	return (new_line);
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

void ft_do_command(t_common *common)
{
	int 		i = 0;
	static char *line;
	char		**lexer_result;

	if (line == NULL || *line == '\0')
	{
		prompt();
		if (-13 == t_get_next_line(&line, common->termcap))
		{
			printf("miniexit\n");
			mini_exit(common);
		}
//		get_next_line(0, &line);

		if (!line || invalid_line(line))
		{
			printf(RED"ERROR line\n"RESET);
//			free(line);
			line = NULL;
			return ;
		}
//		printf("-----------------------------line from gnl - |%s|\n", line);
	}
	t_term_to_cannon(common->termcap);

	if (NULL == (lexer_result = lexer(line, common)))
	{
		line = shift_line_2(line);
		return ;
	}
	if (invalid_lexer_result(lexer_result))
	{
		printf(RED"error in lexer_result\n"RESET);
//		free(line);
		line = NULL;
		return ;
	}
	ft_print_lexer_result(lexer_result);
//	while(lexer_result[i])
//	{
//		free(lexer_result[i]);
//		i++;
//	}

//	fixme раскомментить
	common->command = get_command_table(lexer_result);
	ft_print_all_command(common->command.simple_commands);
	line = shift_line_2(line);
//	fixme раскомментить

//	i = 0;
//	while (1);
//	free(lexer_result);
//	printf(GRN"----------%s\n"RESET, line);
	executor(common);

}

void	minishell_loop(char **envp)
{
	t_common	*common;
	int			i;

	i = 0;
	common = common_init((char **)envp);
	signal_processor();
//	signal(SIGQUIT, handler_s);	// quit	Ctrl+|	выход из приложенияя
	while (1)
	{
		ft_do_command(common);
	}
}

int main(int argc, char const **argv, char const **envp)
{
	(void)argc;
	(void)argv;
	setbuf(stdout, NULL);
	minishell_loop((char **)envp);
	return (0);
}