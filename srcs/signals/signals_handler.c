#include "minishell.h"

/*
Ctrl+D (^D) - [4] EOF means end of file. It only works at the beginning of a line (I'm simplifying a little), and has no effect if the program isn't reading input from the terminal. In your experiment, ^D told the shell that you weren't going to type any more commands, so it exited; then the terminal exited because its subprogram had terminated.

Ctrl+C (^C) - [SIGINT] means “interrupt”, i.e., stop what you're doing. Technically, pressing ^C sends the INT signal, which by default terminates an application, but which in many programs means go back to the top level (e.g., in a shell, stop typing a command line and go back to a pristine prompt).

Ctrl+\ (^\) - [SIGQUIT] try If a program doesn't respond to ^C, you can. This sends the QUIT signal, which by default terminates an application, and which not so many programs intercept.
 */

void	handler_c(int num)
{
	int temp;

	temp = num + 48;
	write(STDOUT_FILENO, &temp, 7);
	write(STDOUT_FILENO, " ctrl_c", 7);
//	exit(0);
}

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

void	signal_handler_command(int num)
{
	if (num == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		errno = 130;	// fixme не знаю насколько это корректное назначение errno
		signal(SIGINT, signal_handler);
	}
}

void	signal_handler(int num)
{
	if (num == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		prompt();
		errno = 1;	// fixme
		signal(SIGINT, signal_handler);
	}
}

void	signal_processor()
{
	signal(SIGINT, signal_handler);	// int	Ctrl+C	завершение ввода без выполнение запуск ввода с начала
	signal(SIGQUIT, signal_handler);	// int	Ctrl+C	завершение ввода без выполнение запуск ввода с начала
}