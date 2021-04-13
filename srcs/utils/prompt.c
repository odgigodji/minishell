#include "minishell.h"

void	prompt(void)
{
	ft_putstr_fd(MAG SHELL_NAME "$ " RESET, STDIN_FILENO);
}
