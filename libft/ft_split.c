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

static void	ft_array_bzero(void *arr, size_t len)
{
	char	**arr_p;

	arr_p = *((char ***)arr);
	while (len--)
	{
		arr_p[len] = NULL;
	}
}

static char	*ft_word_record(char ***split_list_pp, char **s, char sep)
{
	int		count;
	char	**s_l_p;

	count = 0;
	s_l_p = *split_list_pp;
	while (**s == sep && **s != '\0')
		++*s;
	while ((*s)[count] != sep && (*s)[count] != '\0')
		count++;
	if (**s)
		*s_l_p = ft_substr(*s, 0, count);
	*s += count;
	return (*s_l_p);
}

static void	ft_free_list(char ***split_list)
{
	int		count;

	count = 0;
	while ((*split_list)[count] != NULL)
	{
		free((*split_list)[count]);
		count++;
	}
	free((*split_list)[count]);
	free(*split_list);
}

static int	ft_word_count(char const *s, char c)
{
	int	count;
	int	sep_count;

	count = 0;
	sep_count = 0;
	while (s[count] != '\0')
	{
		while (s[count] == c && s[count] != '\0')
			count++;
		if (s[count] != c && s[count] != '\0')
			sep_count++;
		while (s[count] != c && s[count] != '\0')
			count++;
	}
	return (sep_count);
}

char	**ft_split(char const *s, char c)
{
	char	**split_list;
	char	**split_list_p;
	char	*s_p;
	int		words;

	s_p = (char *)s;
	if (!s)
		return (NULL);
	words = ft_word_count(s, c);
	split_list = (char **)malloc((words + 1) * sizeof(char *));
	if (split_list == NULL)
		return (NULL);
	split_list_p = split_list;
	ft_array_bzero(&split_list, words + 1);
	while (words--)
	{
		if (ft_word_record(&split_list_p, &s_p, c) == NULL)
		{
			ft_free_list(&split_list);
			return (NULL);
		}
		split_list_p++;
	}
	return (split_list);
}
