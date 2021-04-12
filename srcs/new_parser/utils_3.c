#include "minishell.h"

char	check_line_1(const char *line)
{
	int	shield_flag;
	int	i;

	i = -1;
	while (line[++i])
	{
		shield_flag = 0;
		if (line[i] == '\\' && !we_are_in_quotes(line, i))
			shield_flag = next_char_is_shielded(line, &i);
		if (!shield_flag && !we_are_in_quotes(line, i))
		{
			if (ft_strchr("{}()&`", line[i]) && !we_are_in_quotes(line, i))
				break ;
			if (line[i] == ';' && !we_are_in_quotes(line, i)
				&& (next_symbol_after_space(line + i + 1) == ';'
					|| next_symbol_after_space(line + i + 1) == '|'))
				break ;
			if (line[i] == '|' && !we_are_in_quotes(line, i)
				&& (next_symbol_after_space(line + i + 1) == ';'
					|| next_symbol_after_space(line + i + 1) == '|'
					|| next_symbol_after_space(line + i + 1) == '\0'))
				break ;
		}
	}
	return (line[i]);
}

int	syntax_error(const char *line)
{
	int		i;
	int		quotes_flag;
	char	quote_type;
	char	res;

	quotes_flag = 0;
	quote_type = 0;
	i = -1;
	if (ft_empty_line(line))
	{
		printf("\n");
		errno = 0;
		return (1);
	}
	if (next_symbol_after_space(line) == ';'
		|| next_symbol_after_space(line) == '|')
	{
		if (next_symbol_after_space(line) == ';')
			return (with_error(';'));
		return (with_error('|'));
	}
	if ((res = check_line_1(line))
		|| (res = check_line_2(line, i, quotes_flag, quote_type)))
		return (with_error(res));
	return (0);
}
