//
// Created by Mariam Scot on 4/8/21.
//

#include "minishell.h"

void	prompt(void)
{
//	ft_putstr_fd("%s$ ", STDIN_FILENO);
	printf(MAG "%s$ " RESET, SHELL_NAME);
}