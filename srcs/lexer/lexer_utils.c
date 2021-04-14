/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mscot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 13:42:13 by mscot             #+#    #+#             */
/*   Updated: 2021/04/14 13:42:14 by mscot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_spec_token_length(char *line, char *token)
{
	if (line[0] == '|')
		return (1);
	else if (line[0] == '>')
	{
		if (line[1] != '>')
			return (1);
		else
			return (2);
	}
	else if (line[0] == '<')
	{
		if (line[1] != '<')
			return (1);
		else
			return (2);
	}
	else if (line[0] == '"' || line[0] == '\'')
		return ((int)strlen(token));
	return (0);
}

int	get_spec_token(char *line, char **token)
{
	if (line[0] == '|')
	{
		*token = strdup(PIPE);
	}
	else if (line[0] == '>')
	{
		if (line[1] != '>')
			*token = strdup(GREAT);
		else
			*token = strdup(GREATGREAT);
	}
	else if (line[0] == '<')
	{
		if (line[1] != '<')
			*token = strdup(LESS);
		else
			*token = strdup(GREATLESS);
	}
	return (get_spec_token_length(line, *token));
}

int	is_spec_symbol(char c)
{
	int	count;

	count = 0;
	while (SPEC_SYMBOL[count])
	{
		if (SPEC_SYMBOL[count] == c)
			return (1);
		count++;
	}
	return (0);
}

int	toggle_back_slash_flag(int flag, char *line, int count)
{
	if (count == 0 || *(line - 1) != '\\')
		return (1);
	else
		return (flag + 1);
}

int	get_token_toggle_flag(t_token_flag *f, char *line, int *count_line)
{
	if (line[*count_line] == '\\'
		&& !f->back_slash
		&& !f->brace_single
		&& (!f->brace_double || ft_strchr("$\\\"\'", line[*count_line + 1])))
	{
		f->back_slash = 1;
		*count_line += 1;
		return (1);
	}
	if (line[*count_line] == '\'' && !f->brace_double && !f->back_slash)
	{
		f->brace_single = !f->brace_single;
		*count_line += 1;
		return (1);
	}
	if (line[*count_line] == '"' && !f->brace_single && !f->back_slash)
	{
		f->brace_double = !f->brace_double;
		*count_line += 1;
		return (1);
	}
	return (0);
}
