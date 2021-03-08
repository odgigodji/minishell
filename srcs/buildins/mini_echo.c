#include "minishell.h"

void	mini_echo(char **simple_command)
{
	int count;

	count = 0;
	ft_putstr_fd(simple_command[0], STDOUT_FILENO);
	while (simple_command[count])
	{
		if (!ft_strncmp(simple_command[count], "-n", 3))
			return ;
	}
	ft_putchar_fd('\n', 1);
}