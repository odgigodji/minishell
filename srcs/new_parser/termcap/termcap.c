//
// Created by Mariam Scot on 4/9/21.
//

#include "minishell.h"

int	ft_putchar_term(int c)
{
	write(1, &c, 1);
	return (c);
}

t_termcap	*t_termcap_init(void)
{
	t_termcap	*result;

	result = malloc(sizeof(t_termcap));
	result->history_len = 10;
	tcgetattr(0, &(result->term));
//	result->history = ft_calloc(result->history_len + 1, sizeof(char *));
	result->history = calloc(result->history_len + 1, sizeof(char *));
	result->history_count = 0;
	result->history_cursor = 0;
	result->term_name = ft_strdup("xterm-256color");
	tgetent(0, result->term_name);
	result->cursor = 0;
	result->line = ft_calloc(MAX_PATH, sizeof(char));
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
		if (!ft_strncmp(line, "\e", 1) || !ft_strncmp(line, keys_list[count],
												ft_strlen(keys_list[count])))
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
		write(1, termcap->history[termcap->history_cursor],
			ft_strlen(termcap->history[termcap->history_cursor]));
		termcap->cursor = ft_strlcpy(termcap->history[termcap->history_count],
			termcap->history[termcap->history_cursor], MAX_PATH);
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
		write(1, termcap->history[termcap->history_cursor],
			ft_strlen(termcap->history[termcap->history_cursor]));
		termcap->cursor = ft_strlcpy(termcap->history[termcap->history_count],
			termcap->history[termcap->history_cursor], MAX_PATH);
	}
	else if (NULL != termcap->history[termcap->history_cursor + 1])
	{
		tputs(restore_cursor, 1, ft_putchar_term);
		tputs(tigetstr("ed"), 1, ft_putchar_term);
		termcap->cursor = ft_strlcpy(termcap->history[termcap->history_count],
							   "", MAX_PATH);
	}
	else
		write(1, "\a", 1);
}

int	t_key_handle(char *buffer, t_termcap *termcap, char **line)
{
	if (!ft_strncmp(buffer, "\e[A", ft_strlen("\e[A")))				// верх
	{
		t_key_handle_up(buffer, termcap, line);
	}
	else if (!ft_strncmp(buffer, "\e[B", ft_strlen("\e[B")))			// низ
		t_key_handle_down(buffer, termcap, line);
	else if (!ft_strncmp(buffer, "\177", 1)) // !strcmp(buffer, key_backspace) || !ft_strncmp(buffer, "\177", 1) ||
	{
		if (termcap->cursor > 0)
		{
			termcap->cursor--;
			termcap->history[termcap->history_count][termcap->cursor] = '\0';
			tputs(cursor_left, 2, ft_putchar_term);
			tputs(tgetstr("dc", 0), 1, ft_putchar_term);
		}
	}
	else
		write(1, "another\n", 0);
	return (0);
}

int		t_input_handle(char *buffer, t_termcap *termcap, char **line)
{
	if (termcap->cursor > 0 && buffer[0] == 4)
	{
		buffer[0] = '\0';
		return (-1);
	}
	if (buffer[0] != '\n')
	{
		if (!ft_strchr("\t\v\f\r\4", buffer[0]))
		{
			termcap->cursor = ft_strlcat(
					termcap->history[termcap->history_count], buffer,
					MAX_PATH);
			write(1, buffer, ft_strlen(buffer));
		}
		return (-1);
	}
	else		// если \n, то записать buffer в конец истории
	{
		termcap->history[termcap->history_count][termcap->cursor] = '\0';
		termcap->history_cursor = termcap->history_count;
		ft_strlcpy(*line, termcap->history[termcap->history_count], MAX_PATH);
		return ((int)ft_strlen(*line));
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
		history_realloc = ft_calloc(termcap->history_len + 1, sizeof(char *));
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
	termcap->history[termcap->history_count] = ft_calloc(MAX_PATH + 1, sizeof(char));
	return (0);
}

int	t_get_next_line(char **line, t_termcap *termcap)
{
	char	buffer[MAX_PATH];
	int		read_rv;
	int		input_rv;
	static int count;

	to_icannon();
	tgetent(0, "xterm-256color");
	buffer[0] = '\0';
	t_history_memory_processing(termcap);
	tputs(save_cursor, 1, ft_putchar_term);
	while (0 != ft_strncmp(buffer, "\4", 1))
	{
		read_rv = read(0, buffer, MAX_PATH);
		buffer[read_rv] = '\0';
		if (is_key(buffer))
			t_key_handle(buffer, termcap, line);
		else
		{
			if (0 <= (input_rv = t_input_handle(buffer, termcap, line)))
			{
				termcap->cursor = 0;
				return (input_rv);
			}
		}
	}
	return (read_rv);
}
