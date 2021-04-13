/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namerei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 16:01:25 by namerei           #+#    #+#             */
/*   Updated: 2020/11/23 14:27:39 by namerei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	need_len;

	i = 0;
	j = 0;
	if (!*needle)
		return ((char *)haystack);
	need_len = ft_strlen(needle);
	while (haystack[i] && i < len)
	{
		while (haystack[i + j] == needle[j] && needle[j] && (i + j) < len)
			j++;
		if (j == need_len)
			return ((char *)&haystack[i]);
		j = 0;
		i++;
	}
	return (NULL);
}
