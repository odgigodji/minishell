#include "minishell.h"

void	minishell_loop(char **envp)
{
	t_common	common;

	common = common_init((char **)envp);
	while (ft_parser(&common))
	{
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