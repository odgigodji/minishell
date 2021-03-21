#include "minishell.h"

void ft_do_command(t_common *common)
{
	//сюда надо функцию работащую с точкой запятой
	int i = 0;
	char *line = NULL;
	get_next_line(0, &line);
//	while(line[i])
//	{
		ft_parser(common, line);
		executor(common);
//	}
}

void	minishell_loop(char **envp)
{
	t_common	common;
	int			i;

	i = 0;
	common = common_init((char **)envp);
	signal_processor();
//	signal(SIGQUIT, handler_s);	// quit	Ctrl+|	выход из приложенияя
	while (1)
	{
		ft_putstr_fd("\033[35mminishell$ \033[0m", 0);
		ft_do_command(&common);
	}
}

int main(int argc, char const **argv, char const **envp)
{
	(void)argc;
	(void)argv;
	minishell_loop((char **)envp);
	return (0);
}