#include <unistd.h>
#include <stdio.h>
#include <term.h>
#include <termios.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return c;
}

//int	main(void)
//{
//	char	str[2048];
//	int		l;
//
//	l = read(0, str, 100);
//	write(1, str, l);
//	return (0);
//}

int main(void)
{
	static char		str[2048];
	int				l;
	struct termios	term;
	char			*term_name = "xterm-256color";
	char			*history[10];
	int				history_count = 0;
	char			*temp;
	char			history_line[2048];
	int				cursor = 0;
	int				count = 0;

	history_line[0] = 0;
	while (10 > history_count)
	{
		history[history_count] = NULL;
		history_count++;
	}
	history_count = 0;
	history[history_count] = calloc(2048, sizeof(char));
	// размеры окна
	struct winsize win;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
//	term.c_lflag |= ECHO;			// восстановление предыдущих (стандартных) параметров
//	term.c_lflag |= ICANON;
	tcsetattr(0, TCSANOW, &term);

	tgetent(0, term_name);
	while (strcmp(str, "\4"))
	{
		history[history_count] = calloc(2048, sizeof(char));
		tputs(save_cursor, 1, ft_putchar);
		do
		{
			l = read(0, str, 100);
			str[l] = '\0';
			if (!strcmp(str, "\e[A"))			// верх
			{
				if (0 < history_count)
					history_count--;
				tputs(restore_cursor, 1, ft_putchar);
				tputs(tigetstr("ed"), 1, ft_putchar);
				write(1, history[history_count], strlen(history[history_count]));
				cursor = strlen(history[history_count]);
			}
			else if (!strcmp(str, "\e[B"))		// низ
			{
				if (NULL != history[history_count + 1])
					history_count++;
				tputs(restore_cursor, 1, ft_putchar);
				tputs(tigetstr("ed"), 1, ft_putchar);
				write(1, history[history_count], strlen(history[history_count]));
				cursor = strlen(history[history_count]);
			}
			else if (!strcmp(str, key_backspace) || !strcmp(str, "\177") || !strcmp(str, "\010"))
			{
				tputs(cursor_left, 2, ft_putchar);
				tputs(tgetstr("dc", 0), 1, ft_putchar);
				history[history_count][strlen(history[history_count]) - 1] = '\0';
				if (cursor > 0)
					cursor--;
			}
			else if (!strcmp(str, "\e[C"))		//право
			{
				if (cursor < strlen(history[history_count]))
				{
					write(1, str, l);
					cursor++;
				}

			}
			else if (!strcmp(str, "\e[D"))		//лево
			{
				write(1, str, l);
				if (cursor > 0)
					cursor--;
			}
			else
			{
				if (l > 0 && str[0] != '\n')
				{
					cursor += l;
					temp = strdup((history[history_count] + cursor - 1));
					history[history_count][cursor - 1] = '\0';
					strncat(history[history_count], str, 2048);
					strncat(history[history_count], temp, 2048);
					write(1, str, l);
					write(1, temp, strlen(temp));
					while (count < strlen(temp))
					{
						write(1, "\e[D", strlen("\e[D"));
						count++;
					}
					count = 0;
				}
				if (str[0] == '\n')
				{
					count = 0;
					while (count < strlen(temp))
					{
						write(1, "\e[C", strlen("\e[C"));
						count++;
					}
					count = 0;
					write(1, str, l);
				}
			}
		} while (strcmp(str, "\n") && strcmp(str, "\4")); // 004 eot
		write(1, history[history_count], strlen(history[history_count]));
		write(1, "\n", 1);
		cursor = 0;
		if (10 > history_count)
			history_count++;
	}
	write(1, "\n", 1);
	history_count = 0;
	while (history[history_count])
	{
		printf("[%2d] %s\n", history_count, history[history_count]);
		history_count++;
	}
	return (0);
}
