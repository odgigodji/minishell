//
// Created by Mariam Scot on 2/24/21.
//

#include "minishell.h"

/*
** string arrays len calculation function
*/



void	ft_putenv_arg(char *line)
{
	int count;
	int flag;

	count = 0;
	flag = 0;
	write(1, "declare -x ", 11);
	while (line[count])
	{
		write(1, &(line[count]), 1);
		if (line[count] == '=')
		{
			flag = 1;
			write(1, "\"", 1);
		}
		count++;
	}
	if (flag)
		write(1, "\"", 1);
	write(1, "\n", 1);
}

void	ft_putenv(char **envp)
{
	int count;

	count = 0;
	while (envp[count])
	{
		ft_putenv_arg(envp[count]);
		count++;
	}
}