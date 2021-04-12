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
				&& (next_after_space(line + i + 1) == ';'
					|| next_after_space(line + i + 1) == '|'))
				break ;
			if (line[i] == '|' && !we_are_in_quotes(line, i)
				&& (next_after_space(line + i + 1) == ';'
					|| next_after_space(line + i + 1) == '|'
					|| next_after_space(line + i + 1) == '\0'))
				break ;
		}
	}
	return (line[i]);
}

int	check_start(const char *line)
{
	if (ft_empty_line(line))
	{
		printf("\n");
		return (1);
	}
	if (next_after_space(line) == ';' || next_after_space(line) == '|')
	{
		if (next_after_space(line) == ';')
			return (with_error(';'));
		return (with_error('|'));
	}
	return (0);
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
	if (check_start(line))
		return (1);
	res = check_line_1(line);
	if (res)
		return (with_error(res));
	res = check_line_2(line, i, quotes_flag, quote_type);
	if (res)
		return (with_error(res));
	return (0);
}

size_t	ft_strlen_to_char(const char *s, char c)
{
	unsigned long	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return ((size_t)len);
}

int	ft_empty_line(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		else
			i++;
	}
	return (1);
}
