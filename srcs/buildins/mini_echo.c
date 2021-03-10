#include "minishell.h"

void	mini_echo(char **simple_command)
{
	int count;
	int count_arg;

	count = 0;
	count_arg = 1;
	if (ft_strncmp(simple_command[count_arg], "-n", 3))
		count_arg++;
	while (simple_command[count_arg])
	{
		ft_putstr_fd(simple_command[count_arg], STDOUT_FILENO);
		ft_putchar_fd(' ', STDOUT_FILENO);
		count_arg++;
	}
	while (simple_command[count])
	{
		if (!ft_strncmp(simple_command[count], "-n", 3))
			return ;
		count++;
	}
	ft_putchar_fd('\n', 1);
}