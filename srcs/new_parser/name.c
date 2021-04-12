#include "minishell.h"

int	next_symbol_after_space(const char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] != ' ' )
			break ;
	}
	return (line[i]);
}

int	with_error(const int unexpected_token)
{
	if (unexpected_token == '\"' || unexpected_token == '\'')
	{
		printf(RED"\nsyntax error : unclosed quotes %c'"RESET, unexpected_token);
		errno = 42;
	}
	else
	{
		if (unexpected_token == 'r')
			printf("minishell: syntax error near redirect\n");
		else
			printf("\nminishell: syntax error near '%c'\n", unexpected_token);
		errno = 258;
	}
	return (1);
}

char	check_line_2(const char *line, int i, int quotes_flag, char quote_type)
{
	int	shield_flag;

	while (line[++i])
	{
		shield_flag = 0;
		if (line[i] == '\\')
			shield_flag = next_char_is_shielded(line, &i);
		if ((line[i] == '\'' || line[i] == '\"')
			&& quotes_flag == 0 && !shield_flag)
		{
			quote_type = line[i];
			quotes_flag = 1;
		}
		else if (line[i] == quote_type && quotes_flag == 1 && !shield_flag)
			quotes_flag = 0;
		if (quotes_flag == 0 && !shield_flag && line[i + 1]
			&& line[i] == '<' && line[i + 1] == '<')
			break ;
		if (quotes_flag == 0 && !shield_flag && line[i + 1] && line[i + 2]
			&& line[i] == '>' && line[i + 1] == '>' && line[i + 2] == '>')
			break ;
	}
	return (line[i]);
}

int	we_are_in_quotes(const char *line, int i)
{
	static int	quotes_open = 0;
	static char	quote_type = '\0';

	if ((line[i] == '\'' || line[i] == '\"') && quotes_open == 0)
	{
		quote_type = line[i];
		quotes_open = 1;
	}
	else if (line[i] == quote_type && quotes_open == 1)
		quotes_open = 0;
	return (quotes_open);
}

int	next_char_is_shielded(const char *line, int *i)
{
	int	slash_counter;

	slash_counter = 0;
	while (line[*i + 1] && line[*i] == '\\')
	{
		slash_counter++;
		*i += 1;
	}
	if (slash_counter % 2 == 0)
		return (0);
	return (1);
}
