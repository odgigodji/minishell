#include "minishell.h"

void	mini_echo(char **simple_command)
{
	int count_arg;

	count_arg = 1;
	while (simple_command[count_arg] && !ft_strncmp(simple_command[count_arg], "-n", 3))
		count_arg++;
	while (simple_command[count_arg])
	{
		ft_putstr_fd(simple_command[count_arg], STDOUT_FILENO);
		if (simple_command[count_arg + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		count_arg++;
	}
	if (simple_command[count_arg] && !ft_strncmp(simple_command[1], "-n", 3))
		return ;
	ft_putchar_fd('\n', 1);
}