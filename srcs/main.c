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
		printf(YEL"|%s|"RESET, arguments[counter]);
}

void ft_print_lexer_result(char **lexer_result)
{
	int count;

	count = 0;
	while (lexer_result && lexer_result[count])
	{
		printf("[%3d] |%10s|\n", count, lexer_result[count]);
		count++;
	}
}

void ft_do_command(t_common *common)
{
	int 		i = 0;
	static char *line;
	char		**lexer_result;
	int			count;

	count = 0;
	if (line == NULL || *line == '\0')
	{
		ft_putstr_fd("\033[35mminishell$ \033[0m", 0);
//		t_get_next_line(&line, common->termcap);
		get_next_line(0, &line);
//		printf("-----------------------------line from gnl - |%s|\n", line);
	}
//	t_term_to_cannon(common->termcap);

	if (!strncmp(line, "exit", 5))
		exit(0);
	lexer_result = lexer(line);
//	braces_expander(lexer_result, common);
	get_command_table(common, lexer_result);
//	count = 0;
//	while (lexer_result && lexer_result[count])
//	{
//		printf("[%3d] |%10s|\n", count, lexer_result[count]);
//		count++;
//	}
	line = NULL;

//	line += new_pars(common, line); // смещаем line на расстояние до точки с запятой

//	executor(common);

//		printf(CYN"----------------------------------------------------------end of executor---------------------------------------------------\n"RESET);
//	if (*line == '\0')
//		printf("==================================================the end of line\n");
//	printf("-------------------------------line after ';' is <%s>\n", line);

//	}
}

void	minishell_loop(char **envp)
{
	t_common	*common;
	int			i;

	i = 0;
	common = common_init((char **)envp);
//	signal_processor();
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