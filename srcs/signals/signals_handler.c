#include "minishell.h"

/*
Ctrl+D (^D) - [4] EOF means end of file. It only works at the beginning of a line (I'm simplifying a little), and has no effect if the program isn't reading input from the terminal. In your experiment, ^D told the shell that you weren't going to type any more commands, so it exited; then the terminal exited because its subprogram had terminated.

Ctrl+C (^C) - [SIGINT] means “interrupt”, i.e., stop what you're doing. Technically, pressing ^C sends the INT signal, which by default terminates an application, but which in many programs means go back to the top level (e.g., in a shell, stop typing a command line and go back to a pristine prompt).

Ctrl+\ (^\) - [SIGQUIT] try If a program doesn't respond to ^C, you can. This sends the QUIT signal, which by default terminates an application, and which not so many programs intercept.
 */

//void	signals_handler(void)
//{
//	signal(SIGINT, handler);
//	signal(4, handler);			// EOT Ctrl+D
//	signal(SIGQUIT, handler);	// EOT Ctrl+/
//}

/*
** Handles interruption signals on the program
**
** @param		num		The signal number
** @return		N/A
*/

void	signal_handler(int num)
{
	if (num == SIGINT)
	{
		if (g_signal_process_status)
		{
			ft_putstr_fd("\r^C\n", 1);
			g_signal_process_status = 0;
			errno = 130;
		}
		else
		{
			ft_putstr_fd("  \n", 1);
			prompt();
		}
	}
	if (num == SIGQUIT)
	{
		if (g_signal_process_status)
		{
			g_signal_process_status = 0;
			errno = 3;
			ft_putstr_fd("Quit: 3\n", 1);
		}
		else
			ft_putstr_fd("\b\b  \b\b", 1);
	}
}

void	signal_processor(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}