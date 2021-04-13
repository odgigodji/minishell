/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namerei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 18:13:54 by namerei           #+#    #+#             */
/*   Updated: 2020/11/18 20:17:29 by namerei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		q(int nb, int fd)
{
	char	a;

	if (!nb)
		return ;
	q(nb / 10, fd);
	a = nb % 10 + '0';
	write(fd, &a, 1);
}

void		ft_putnbr_fd(int nb, int fd)
{
	if (nb == 0 || nb == -2147483648)
	{
		write(fd, (nb == 0) ? "0" : "-2147483648", (nb == 0) ? 1 : 11);
		return ;
	}
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb = -nb;
	}
	q(nb, fd);
}
