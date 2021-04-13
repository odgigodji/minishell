/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namerei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 22:16:08 by namerei           #+#    #+#             */
/*   Updated: 2020/11/19 22:46:57 by namerei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrev(char *s)
{
	int		start;
	int		end;
	char	tmp;
	int		len;

	start = 0;
	end = ft_strlen(s) - 1;
	tmp = 0;
	len = end;
	while (start != (len / 2) + 1)
	{
		tmp = s[start];
		s[start] = s[end];
		s[end] = tmp;
		start++;
		end--;
	}
	return (s);
}
