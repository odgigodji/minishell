#include "minishell.h"

void	handler(int num)
{
	write(STDOUT_FILENO, "\n", 1);
	exit(0);
}

void	signals_handler(void)
{
	signal(SIGINT, handler);
}