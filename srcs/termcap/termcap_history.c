/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mscot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 13:43:41 by mscot             #+#    #+#             */
/*   Updated: 2021/04/14 13:43:43 by mscot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_history_len(char **history)
{
	int	count;

	count = 0;
	while (history[count])
		count++;
	return (count);
}

void	t_history_memory_pr_no_realloc(t_termcap *termcap, int history_len)
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

int	t_history_memory_pr_realloc(t_termcap *termcap)
{
	char	**history_realloc;
	int		count;

	count = 0;
	termcap->history_len += 10;
	history_realloc = malloc((termcap->history_len + 1) * sizeof(char *));
	if (NULL == history_realloc)
		return (-1);
	while (termcap->history[count])
	{
		history_realloc[count] = termcap->history[count];
		count++;
	}
	history_realloc[count] = NULL;
	free(termcap->history);
	termcap->history = history_realloc;
	termcap->history_count = count;
	return (0);
}

int	t_history_memory_processing(t_termcap *termcap)
{
	int		history_len;

	history_len = get_history_len(termcap->history);
	if (history_len < termcap->history_len)
	{
		t_history_memory_pr_no_realloc(termcap, history_len);
	}
	else
	{
		if (t_history_memory_pr_realloc(termcap))
			return (-1);
	}
	termcap->history_cursor = termcap->history_count;
	termcap->history[termcap->history_count] = malloc(
			(MAX_PATH + 1) * sizeof(char));
	if (NULL == termcap->history[termcap->history_count])
		return (-1);
	termcap->history[termcap->history_count][0] = '\0';
	termcap->history[termcap->history_count + 1] = NULL;
	return (0);
}
