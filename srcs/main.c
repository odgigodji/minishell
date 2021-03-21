#include "minishell.h"

void	minishell_loop(char **envp)
{
	t_common	common;
	int			i;

	i = 0;
	common = common_init((char **)envp);
	signal_processor();
//	signal(SIGQUIT, handler_s);	// quit	Ctrl+|	выход из приложенияя
	while (ft_parser(&common))
	{
//		while(common.command.simple_commands[0]->arguments[i])
//		{
//			printf("%d argument is |%s|\n", i, common.command.simple_commands[0]->arguments[i]);
//			i++;
//		}
//		if (common.command.simple_commands[0]->arguments[i] == NULL)
//			printf("%d argument is |null|\n", i);
		executor(&common);
	}
	while (ft_parser(&common))
	{
//		while(common.command.simple_commands[0]->arguments[i])
//		{
//			printf("%d argument is |%s|\n", i, common.command.simple_commands[0]->arguments[i]);
//			i++;
//		}
//		if (common.command.simple_commands[0]->arguments[i] == NULL)
//			printf("%d argument is |null|\n", i);
		executor(&common);
	}
}

int main(int argc, char const **argv, char const **envp)
{
	(void)argc;
	(void)argv;
	minishell_loop((char **)envp);
	return (0);
}