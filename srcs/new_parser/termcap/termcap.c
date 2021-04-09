//
// Created by Mariam Scot on 4/9/21.
//

#include "minishell.h"

int	ft_putchar_term(int c)
{
	write(1, &c, 1);
	return c;
}

t_termcap	*t_termcap_init(void)
{
	t_termcap	*result;

	result = malloc(sizeof(t_termcap));
	result->history_len = 10;
	tcgetattr(0, &(result->term));
	result->history = calloc(result->history_len + 1, sizeof(char *));
	result->history_count = 0;
	result->history_cursor = 0;
	result->term_name = strdup("xterm-256color");
	tgetent(0, result->term_name);
	result->cursor = 0;
	return (result);
}

void	to_icannon(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
}

void	to_cannon(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag |= ECHO;			// восстановление предыдущих (стандартных) параметров
	term.c_lflag |= ICANON;
	tcsetattr(0, TCSANOW, &term);
}

int	is_key(char *line)
{
	char *keys_list[] = {"\e[A", "\e[B", "\010", "\177", "\e[C", "\e[D", NULL};
	int count;

	count = 0;
	while (keys_list[count])
	{
		if (!strncmp(line, "\e", 1) || !strncmp(line, keys_list[count], strlen(keys_list[count])))
		{
			return (1);
		}
		count++;
	}
	return (0);
}

void	t_key_handle_up(char *buffer, t_termcap *termcap, char **line)
{
	if (0 < termcap->history_cursor)
	{
		termcap->history_cursor--;
		tputs(restore_cursor, 1, ft_putchar_term);
		tputs(tigetstr("ed"), 1, ft_putchar_term);
		write(1, termcap->history[termcap->history_cursor], strlen(termcap->history[termcap->history_cursor]));
		termcap->cursor = strlcpy(termcap->history[termcap->history_count], termcap->history[termcap->history_cursor], MAX_PATH);
	}
	else
		write(1, "\a", 1);
}

void	t_key_handle_down(char *buffer, t_termcap *termcap, char **line)
{
	if (NULL != termcap->history[termcap->history_cursor + 2])
	{
		termcap->history_cursor++;
		tputs(restore_cursor, 1, ft_putchar_term);
		tputs(tigetstr("ed"), 1, ft_putchar_term);
		write(1, termcap->history[termcap->history_cursor], strlen(termcap->history[termcap->history_cursor]));
		termcap->cursor = strlcpy(termcap->history[termcap->history_count], termcap->history[termcap->history_cursor], MAX_PATH);
	}
	else if (NULL != termcap->history[termcap->history_cursor + 1])
	{
		tputs(restore_cursor, 1, ft_putchar_term);
		tputs(tigetstr("ed"), 1, ft_putchar_term);
		termcap->cursor = strlcpy(termcap->history[termcap->history_count], "", MAX_PATH);
	}
	else
		write(1, "\a", 1);
}

int	t_key_handle(char *buffer, t_termcap *termcap, char **line)
{
	if (!strcmp(buffer, "\e[A"))				// верх
	{
		t_key_handle_up(buffer, termcap, line);
	}
	else if (!strcmp(buffer, "\e[B"))			// низ
		t_key_handle_down(buffer, termcap, line);
	else if (!strcmp(buffer, key_backspace) || !strcmp(buffer, "\177") || !strcmp(buffer, "\010"))
	{
		if (termcap->cursor > 0)
		{
			termcap->cursor--;
			termcap->history[termcap->history_count][termcap->cursor] = '\0';
			tputs(cursor_left, 2, ft_putchar_term);
			tputs(tgetstr("dc", 0), 1, ft_putchar_term);
		}
	}
	else if (!strcmp(buffer, "\e[C"))			//право
		write(1, "right\n", 0);
	else if (!strcmp(buffer, "\e[D"))			//лево
		write(1, "left\n", 0);
	else
		write(1, "another\n", 0);
	return (0);
}

int		t_input_handle(char *buffer, t_termcap *termcap, char **line)
{
	if (buffer[0] != '\n')
	{
		termcap->cursor = strlcat(termcap->history[termcap->history_count], buffer, MAX_PATH);
		write(1, buffer, strlen(buffer));
//		termcap->history_cursor = termcap->history_count;
		return (-1);
	}
	else		// если \n, то записать buffer в конец истории
	{
		termcap->history[termcap->history_count][termcap->cursor] = '\0';
		termcap->history_cursor = termcap->history_count;
		*line = strdup(termcap->history[termcap->history_count]);
		return ((int)strlen(*line));
	}
}

int	get_history_len(char **history)
{
	int count;

	count = 0;
	while (history[count])
		count++;
	return (count);
}

int	t_history_memory_processing(t_termcap *termcap)
{
	int		history_len;
	char	**history_realloc;
	int 	count;

	history_len = get_history_len(termcap->history);
	count = 0;
	if (history_len < termcap->history_len)
	{
		if (history_len > 0 && termcap->history[history_len - 1][0] == '\0')
		{
			free(termcap->history[history_len - 1]);
			termcap->history[history_len - 1] = NULL;
			termcap->history_count = history_len - 1;
		}
		else
			termcap->history_count = history_len;
	}
	else
	{
		termcap->history_len += 10;
		history_realloc = calloc(termcap->history_len + 1, sizeof(char *));
		while (termcap->history[count])
		{
			history_realloc[count] = termcap->history[count];
			count++;
		}
		free(termcap->history);
		termcap->history = history_realloc;
		termcap->history_count = count;
	}
	termcap->history_cursor = termcap->history_count;
	termcap->history[termcap->history_count] = calloc(MAX_PATH + 1, sizeof(char));
	return (0);
}

int	t_get_next_line(char **line, t_termcap *termcap)
{
	char	*term_name = "xterm-256color";
	char	buffer[MAX_PATH];
	int		read_rv;
	int		input_rv;

	to_icannon();
	tgetent(0, term_name);
	buffer[0] = '\0';
	t_history_memory_processing(termcap);
	tputs(save_cursor, 1, ft_putchar_term);
	while (0 != strncmp(buffer, "\4", 1))
	{
		read_rv = read(0, buffer, MAX_PATH);
		buffer[read_rv] = '\0';
		if (is_key(buffer))
			t_key_handle(buffer, termcap, line);
		else
		{
			if (0 <= (input_rv = t_input_handle(buffer, termcap, line)))
				return (input_rv);
		}
	}
	return (0);
}
