/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namerei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 22:03:10 by namerei           #+#    #+#             */
/*   Updated: 2021/02/04 22:03:46 by namerei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *buf;

	if (!(*lst))
		*lst = new;
	else
	{
		buf = *lst;
		while (buf->next)
			buf = buf->next;
		buf->next = new;
	}
}
