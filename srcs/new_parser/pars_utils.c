#include "minishell.h"

size_t	ft_strlen_to_char(const char *s, char c)
{
	unsigned long len;

	len = 0;
	if (!(ft_strchr(s, c)))
		return (0);
	while (s[len] && s[len] != c)
		len++;
	return ((size_t)len);
}