#include "minishell.h"

int		is_n_key(char *key)
{
	int	count;

	count = 1;
	while (key[count])
	{
		if (key[count] != 'n')
			return (0);
		count++;
	}
	return (1);
}

void	mini_echo(char **simple_command)
{
	int count_arg;

	count_arg = 1;
	while (simple_command[count_arg]
		&& (!ft_strncmp(simple_command[count_arg], "-n", 2) && is_n_key(simple_command[count_arg])))
	{
		count_arg++;
	}
	while (simple_command[count_arg])
	{
		ft_putstr_fd(simple_command[count_arg], STDOUT_FILENO);
		if (simple_command[count_arg + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		count_arg++;
	}
	if (simple_command[1] && !ft_strncmp(simple_command[1], "-n", 3))
	{
		return;
	}
	g_errno = 0;
	ft_putchar_fd('\n', 1);
}