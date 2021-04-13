/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namerei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 15:49:47 by namerei           #+#    #+#             */
/*   Updated: 2020/11/19 21:34:47 by namerei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_str_counter(char *s, int c)
{
	int		count;

	count = 0;
	while (*s)
	{
		if ((*s != c && *(s + 1) == c) || (*s != c && (*(s + 1) == '\0')))
			count++;
		s++;
	}
	return (count);
}

static char	**ft_free_str(char **res, int i)
{
	if (!i)
	{
		i--;
		while (i >= 0)
		{
			free(res[i]);
			i--;
		}
	}
	free(res);
	return (res);
}

static char	**ft_result(const char *s, char **q, char c)
{
	int		i;
	int		k;
	int		symb_count;

	i = 0;
	k = 0;
	symb_count = 0;
	while (k < (int)ft_strlen(s) && i < ft_str_counter((char *)s, c))
	{
		if (s[k] != c)
		{
			while (s[k] != c && s[k])
			{
				symb_count++;
				k++;
			}
			if (!(q[i] = ft_substr(s, k - symb_count, symb_count)))
				return (ft_free_str(q, i));
			symb_count = 0;
			i++;
		}
		k++;
	}
	q[i] = NULL;
	return (q);
}

char		**ft_split(char const *s, char c)
{
	char	**q;

	if (!s || !(q = (char **)malloc(sizeof(char *) * \
	(ft_str_counter((char *)s, c) + 1))))
		return (NULL);
	return (ft_result(s, q, c));
}
