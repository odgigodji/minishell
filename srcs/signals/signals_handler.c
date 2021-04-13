#include "minishell.h"

void	signal_handler_int(int num)
{
	if (num == SIGINT)
	{
		ft_putstr_fd("\r^C\n", 1);
		g_errno = 130;
		to_cannon();
		tputs(save_cursor, 1, ft_putchar_term);
	}
}

void	signal_handler_quit(int num)
{
	if (num == SIGQUIT)
	{
		g_errno = 3;
		ft_putstr_fd("Quit: 3\n", 1);
	}
}

void	signal_processor(void)
{
	signal(SIGINT, signal_handler_int);
	signal(SIGQUIT, signal_handler_quit);
	signal(SIGTERM, signal_handler_quit);
}
