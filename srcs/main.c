#include "minishell.h"

void ft_do_command(t_common *common)
{
	int i = 0;
	static char *line;

	if (line == NULL || *line == '\0')
	{
		ft_putstr_fd("\033[35mminishell$ \033[0m", 0);
//		t_get_next_line(&line, common->termcap);
		get_next_line(0, &line);
//		printf("-----------------------------line from gnl - |%s|\n", line);
	}
//	t_term_to_cannon(common->termcap);
	line += ft_parser(common, line); // смещаем line на расстояние до точки с запятой
//		 ft_shift_line_beyond_semicolon(line) + 1;

//		line += 5;
	executor(common);

//		printf(CYN"----------------------------------------------------------end of executor---------------------------------------------------\n"RESET);
//	if (*line == '\0')
//		printf("==================================================the end of line\n");
//	printf("-------------------------------line after ';' is <%s>\n", line);

//	}
}

void	minishell_loop(char **envp)
{
	t_common	common;
	int			i;

	i = 0;
	common = common_init((char **)envp);
//	signal_processor();
//	signal(SIGQUIT, handler_s);	// quit	Ctrl+|	выход из приложенияя
	while (1)
	{
//		ft_putstr_fd("\033[35mminishell$ \033[0m", 0);
		ft_do_command(&common);
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