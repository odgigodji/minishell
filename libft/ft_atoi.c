/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namerei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 14:38:10 by namerei           #+#    #+#             */
/*   Updated: 2020/11/19 15:44:30 by namerei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	flag;
	int	num;

	flag = 1;
	num = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == 45)
		flag = -1;
	if (*str == 45 || *str == 43)
		str++;
	while (*str >= 48 && *str <= 57)
		num = num * 10 + (*str++ - 48);
	return (num * flag);
}
