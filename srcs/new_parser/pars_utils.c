#include "minishell.h"

size_t	ft_strlen_to_char(const char *s, char c)
{
	unsigned long len;

	len = 0;
//	if (!(ft_strchr(s, c)))
//		return (-1); // не нашли чара до которого считать длинну
	while (s[len] && s[len] != c)
		len++;
	return ((size_t)len);
}

int	ft_empty_line(const char *line)
{
	int i;

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
