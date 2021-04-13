#include "minishell.h"

int	is_key(char *line)
{
	char	*keys_list[7];
	int		count;

	count = 0;
	keys_list[0] = "\e[A";
	keys_list[1] = "\e[B";
	keys_list[2] = "\010";
	keys_list[3] = "\177";
	keys_list[4] = "\e[C";
	keys_list[5] = "\e[D";
	keys_list[6] = NULL;
	while (keys_list[count])
	{
		if (!ft_strncmp(line, "\e", 1)
			|| !ft_strncmp(line, keys_list[count],
				  ft_strlen(keys_list[count])))
		{
			return (1);
		}
		count++;
	}
	return (0);
}

void	t_key_handle_up(t_termcap *termcap)
{
	if (0 < termcap->history_cursor)
	{
		termcap->history_cursor--;
		tputs(restore_cursor, 1, ft_putchar_term);
		tputs(tigetstr("ed"), 1, ft_putchar_term);
		write(1, termcap->history[termcap->history_cursor],
			  ft_strlen(termcap->history[termcap->history_cursor]));
		termcap->cursor = ft_strlcpy(termcap->history[termcap->history_count],
				 termcap->history[termcap->history_cursor],
				 MAX_PATH);
	}
	else
		write(1, "\a", 1);
}

void	t_key_handle_down(t_termcap *termcap)
{
	tputs(restore_cursor, 1, ft_putchar_term);
	tputs(tigetstr("ed"), 1, ft_putchar_term);
	if ((NULL != termcap->history[termcap->history_cursor + 1])
		&& termcap->history_cursor + 2 < get_history_len(termcap->history))
	{
		termcap->history_cursor++;
		write(1, termcap->history[termcap->history_cursor],
			  ft_strlen(termcap->history[termcap->history_cursor]));
		termcap->cursor = ft_strlcpy(termcap->history[termcap->history_count],
				 termcap->history[termcap->history_cursor],
				 MAX_PATH);
	}
	else if (termcap->history_cursor + 1 < get_history_len(termcap->history))
	{
		termcap->history_cursor++;
		termcap->cursor = ft_strlcpy(termcap->history[termcap->history_count],
				"", MAX_PATH);
	}
	else
		write(1, "\a", 1);
}

int	t_key_handle(char *buffer, t_termcap *termcap)
{
	if (!ft_strncmp(buffer, "\e[A", ft_strlen("\e[A")))
	{
		t_key_handle_up(termcap);
	}
	else if (!ft_strncmp(buffer, "\e[B", ft_strlen("\e[B")))
		t_key_handle_down(termcap);
	else if (!ft_strncmp(buffer, "\177", 1))
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
