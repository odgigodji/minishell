/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namerei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 22:28:44 by namerei           #+#    #+#             */
/*   Updated: 2021/01/18 17:37:58 by namerei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*(char *)s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	unsigned long len;

	len = 0;
	while (s[len])
		len++;
	return ((size_t)len);
}

char	*ft_strdup(const char *s1)
{
	char	*res;
	size_t	i;

	i = 0;
	res = (char *)malloc(ft_strlen(s1) + 1);
	if (!res)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

void	*ft_calloc(size_t count, size_t size)
{
	void			*res;
	unsigned char	*x;

	res = malloc(count * size);
	x = (unsigned char*)res;
	if (res == NULL)
		return (res);
	while (size--)
		*x++ = 0;
	return (res);
}

char	*ft_strjoin_with_free(char *s1, char *s2)
{
	size_t	len;
	size_t	i;
	char	*res;

	i = 0;
	if (!s1)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	res = (char *)malloc(len + 1);
	if (!res)
		return (res);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (*s2)
	{
		res[i] = *s2++;
		i++;
	}
	res[i] = '\0';
	free(s1);
	return (res);
}
