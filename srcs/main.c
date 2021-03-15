#include "minishell.h"

void	minishell_loop(char **envp)
{
	t_common	common;
	int i;

	i = 0;
	common = common_init((char **)envp);
//	ft_putstr_fd("\033[35mminishell$ \033[0m", 0);
	while (ft_parser(&common))
	{
//		ft_putstr_fd("\033[35mminishell$ \033[0m", 0);
		executor(&common);
//		while(common.command.simple_commands[0]->arguments[i])
//		{
//			free(common.command.simple_commands[0]->arguments[0]);
//			free(common.command.simple_commands[0]->arguments[1]);
//			i++;
//		}
//		free(common.command.simple_commands[0]);
//		free(common.command.simple_commands);
	}
}

int main(int argc, char const **argv, char const **envp)
{
	(void)argc;
	(void)argv;
	minishell_loop((char **)envp);
	return (0);
}