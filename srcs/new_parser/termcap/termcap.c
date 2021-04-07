#include "minishell.h"

int	ft_putchar_term(int c)
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

int	t_key_up(t_termcap *termcap, char **history, int *history_count)
{
	if (0 < termcap->history_count)
		termcap->history_count--;
	tputs(restore_cursor, 1, ft_putchar_term);
	tputs(tigetstr("ed"), 1, ft_putchar_term);
	write(1, termcap->history[termcap->history_count], strlen(termcap->history[termcap->history_count]));
	termcap->cursor = strlen(termcap->history[termcap->history_count]);
	return (termcap->cursor);
}

int	t_key_down(t_termcap *termcap, char **history, int *history_count)
{
	if (NULL != termcap->history[termcap->history_count + 1])
		termcap->history_count++;
	tputs(restore_cursor, 1, ft_putchar_term);
	tputs(tigetstr("ed"), 1, ft_putchar_term);
	write(1, termcap->history[termcap->history_count], strlen(termcap->history[termcap->history_count]));
	termcap->cursor = strlen(termcap->history[termcap->history_count]);
	return (termcap->cursor);
}

int	t_key_back(t_termcap *termcap, char **history, int *history_count, int cursor)
{
	tputs(cursor_left, 2, ft_putchar_term);
	tputs(tgetstr("dc", 0), 1, ft_putchar_term);
	termcap->history[termcap->history_count][strlen(termcap->history[termcap->history_count]) - 1] = '\0';
	if (termcap->cursor > 0)
		termcap->cursor--;
	return (termcap->cursor);
}

int	t_key_right(t_termcap *termcap, char **history, int *history_count, int cursor, char *str)
{
	if (termcap->cursor < strlen(termcap->history[termcap->history_count]))
	{
		write(STDOUT_FILENO, str, strlen(str));
		termcap->cursor++;
	}
	return (termcap->cursor);
}

int	t_key_left(t_termcap *termcap, char **history, int *history_count, int cursor, char *str)
{
	if (termcap->cursor > 0)
	{
		write(STDOUT_FILENO, str, strlen(str));
		termcap->cursor--;
	}
	return (termcap->cursor);
}

int	t_key_handle(t_termcap *termcap, char **history, int *history_count, int cursor, char *str)
{
	if (!strcmp(str, "\e[A"))			// верх
		termcap->cursor = t_key_up(termcap, history, history_count);
	else if (!strcmp(str, "\e[B"))		// низ
		termcap->cursor = t_key_down(termcap, history, history_count);
	else if (!strcmp(str, key_backspace) || !strcmp(str, "\177") || !strcmp(str, "\010"))
		termcap->cursor = t_key_back(termcap, history, history_count, cursor);
	else if (!strcmp(str, "\e[C"))		//право
		termcap->cursor = t_key_right(termcap, history, history_count, cursor, str);
	else if (!strcmp(str, "\e[D"))		//лево
		termcap->cursor = t_key_left(termcap, history, history_count, cursor, str);
	return (termcap->cursor);
}

int	t_is_key(char *str)
{
	if (!strcmp(str, "\e[A")
		|| !strcmp(str, "\e[B")
		|| !strcmp(str, key_backspace)
		|| !strcmp(str, "\177")
		|| !strcmp(str, "\010")
		|| !strcmp(str, "\e[C")
		|| !strcmp(str, "\e[D")
			)
		return (1);
	return (0);
}

t_termcap	*t_termcap_init(void)
{
	t_termcap	*result;

	result = malloc(sizeof(t_termcap));
	result->history_len = 100;
	tcgetattr(0, &(result->term));
	result->history = calloc(result->history_len, sizeof(char *));
	result->history[0] = calloc(2048, sizeof(char));
	result->history_count = 0;
	result->term_name = strdup("xterm-256color");
	tgetent(0, result->term_name);
	result->cursor = 0;
	return (result);
}

void	t_term_to_icannon(t_termcap *termcap) // в неканнонический режим
{
	tcgetattr(0, &(termcap->term));
	termcap->term.c_lflag &= ~(ECHO);
	termcap->term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &(termcap->term));
}

void	t_term_to_cannon(t_termcap *termcap)
{
	tcgetattr(0, &(termcap->term));
	termcap->term.c_lflag |= ECHO;			// восстановление предыдущих (стандартных, каннонических) параметров
	termcap->term.c_lflag |= ICANON;
	tcsetattr(0, TCSANOW, &(termcap->term));
}

void	t_print_history(t_termcap *termcap)
{
	int	count;

	count = 0;
	while (termcap->history[count])
	{
		printf("[%2d] %s\n", count, termcap->history[count]);
		count++;
	}
}

void	move_cursor_right_c(char *line)
{
	int count;

	count = 0;
	while (count < strlen(line))
	{
		write(1, "\e[C", strlen("\e[C"));
		count++;
	}
}

void	move_cursor_left_d(char *line)
{
	int	count;

	count = 0;
	while (count < strlen(line))
	{
		write(1, "\e[D", strlen("\e[D"));
		count++;
	}
}

void	t_not_cr(t_termcap *termcap, int l, char *str)
{
	termcap->cursor += l;
	termcap->temp = strdup((termcap->history[termcap->history_count] + termcap->cursor - 1));
	termcap->history[termcap->history_count][termcap->cursor - 1] = '\0';
	strncat(termcap->history[termcap->history_count], str, MAX_PATH);
	strncat(termcap->history[termcap->history_count], termcap->temp, MAX_PATH);
	write(1, str, l);
	write(1, termcap->temp, strlen(termcap->temp));
}

int	t_string_handle(t_termcap *termcap, char *str, int l)
{
	termcap->temp = strdup("");
	if (t_is_key(str))
		termcap->cursor = t_key_handle(termcap, termcap->history,
									   &(termcap->history_count), termcap->cursor, str);
	else
	{
		if (l > 0 && str[0] != '\n')
		{
			t_not_cr(termcap, l, str);
			move_cursor_left_d(termcap->temp);
		}
		else if (l == 1 && str[0] == '\n')
		{
			move_cursor_right_c(termcap->temp);
			return (0);
		}
	}
	return (1);
}

int	t_get_next_line(char **line, t_termcap *termcap)
{
	char	str[MAX_PATH];
	int		l;

	t_term_to_icannon(termcap);
	str[0] = '\0';
	termcap->history[termcap->history_count] = calloc(MAX_PATH, sizeof(char));
	tputs(save_cursor, 1, ft_putchar_term);
//	while (str[0] != '\n')					// 004 eot
	while (0 != strcmp(str, "\4"))			// 004 eot
	{
		if (0 >= (l = read(0, str, 100)))
			return (l);
		str[l] = '\0';
		if (0 == l || !t_string_handle(termcap, str, l))  // || !strcmp(str, "\n")
			break ;
	}
	termcap->cursor = 0;
	if (str[0] != '\n' && 0 <= termcap->history_count) //
		*line = strdup(termcap->history[termcap->history_count]);   //termcap->history_count - 1
	else
	{
		*line = strdup(termcap->history[termcap->history_count]);
		write(1, "\n", 1);
	}
	if (termcap->history_len > termcap->history_count)
		termcap->history_count++;
	return ((int)strlen(*line));
}

//int main(void)
//{
//	char		*line;
//	t_termcap	*termcap;
//	int			rv;
//
//	termcap = t_termcap_init();
//	rv = 1;
//	while (rv)
//	{
//		rv = t_get_next_line(&line, termcap);
//		printf("<<<%s>>>\n", line);
//	}
//	return (0);
//}