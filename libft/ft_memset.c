/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namerei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 18:08:32 by namerei           #+#    #+#             */
/*   Updated: 2020/11/18 18:08:34 by namerei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *x;
	unsigned char z;

	x = (unsigned char*)b;
	z = (unsigned char)c;
	while (len > 0)
	{
		*x++ = c;
		len--;
	}
	return ((unsigned char*)b);
}
