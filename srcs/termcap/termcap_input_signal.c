/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_input_signal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mscot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 13:44:00 by mscot             #+#    #+#             */
/*   Updated: 2021/04/14 13:44:01 by mscot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	t_is_signal(char *buffer, t_termcap *termcap)
{
	if (termcap->cursor > 0 && buffer[0] == 4)
		return (1);
	if (buffer[0] == 3)
		return (1);
	if (buffer[0] == 28)
		return (1);
	return (0);
}

int	t_handle_signal(char *buffer, t_termcap *termcap)
{
	if (termcap->cursor > 0 && buffer[0] == 4)
	{
		buffer[0] = '\0';
		return (-1);
	}
	if (buffer[0] == 3)
	{
		buffer[0] = '\0';
		return (0);
	}
	if (buffer[0] == 28)
	{
		buffer[0] = '\0';
		return (-1);
	}
	return (0);
}

int	t_input_handle(char *buffer, t_termcap *termcap, char **line)
{
	if (t_is_signal(buffer, termcap))
		return (t_handle_signal(buffer, termcap));
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
	else
	{
		termcap->history[termcap->history_count][termcap->cursor] = '\0';
		termcap->history_cursor = termcap->history_count;
		ft_strlcpy(*line, termcap->history[termcap->history_count], MAX_PATH);
		return ((int)ft_strlen(*line));
	}
}

int	t_termcap_pre(t_termcap *termcap)
{
	to_icannon();
	tgetent(0, "xterm-256color");
	if (-1 == t_history_memory_processing(termcap))
		return (-1);
	tputs(save_cursor, 1, ft_putchar_term);
	return (0);
}

int	t_termcap_input_handle(char *buffer,
							  t_termcap *termcap,
							  char **line)
{
	int	input_rv;

	input_rv = t_input_handle(buffer, termcap, line);
	if (0 <= input_rv)
	{
		termcap->cursor = 0;
	}
	return (input_rv);
}
