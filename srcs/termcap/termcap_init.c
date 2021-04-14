/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mscot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 13:43:50 by mscot             #+#    #+#             */
/*   Updated: 2021/04/14 13:43:52 by mscot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	result->history = malloc((result->history_len + 1) * sizeof(char *));
	result->history[0] = NULL;
	result->history_count = 0;
	result->history_cursor = 0;
	result->term_name = ft_strdup("xterm-256color");
	tgetent(0, result->term_name);
	result->cursor = 0;
	result->line = malloc((MAX_PATH + 1) * sizeof(char));
	result->line[0] = '\0';
	return (result);
}

void	to_icannon(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO | ISIG);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
}

void	to_cannon(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag |= (ECHO | ISIG);
	term.c_lflag |= ICANON;
	tcsetattr(0, TCSANOW, &term);
}
