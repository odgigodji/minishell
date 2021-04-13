/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namerei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 18:30:08 by namerei           #+#    #+#             */
/*   Updated: 2020/11/18 22:23:05 by namerei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*res;

	i = 0;
	res = (char *)malloc(len + 1);
	if (!res || !s)
		return (NULL);
	while (i < len && start < ft_strlen(s))
		res[i++] = s[start++];
	res[i] = '\0';
	return (res);
}
