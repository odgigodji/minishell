#include "minishell.h"

/*
Ctrl+D (^D) - [] EOF means end of file. It only works at the beginning of a line (I'm simplifying a little), and has no effect if the program isn't reading input from the terminal. In your experiment, ^D told the shell that you weren't going to type any more commands, so it exited; then the terminal exited because its subprogram had terminated.

Ctrl+C (^C) - [SIGINT] means “interrupt”, i.e., stop what you're doing. Technically, pressing ^C sends the INT signal, which by default terminates an application, but which in many programs means go back to the top level (e.g., in a shell, stop typing a command line and go back to a pristine prompt).

Ctrl+\ (^\) - [SIGQUIT] try If a program doesn't respond to ^C, you can. This sends the QUIT signal, which by default terminates an application, and which not so many programs intercept.
 */

void	handler(int num)
{
	write(STDOUT_FILENO, "\n", 1);
//	exit(0);
}

void	signals_handler(void)
{
	signal(SIGINT, handler);
}