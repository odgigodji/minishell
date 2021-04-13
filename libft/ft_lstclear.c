/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namerei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 22:14:04 by namerei           #+#    #+#             */
/*   Updated: 2021/02/04 22:14:34 by namerei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *buf;

	while (*lst)
	{
		buf = (*lst)->next;
		(*del)((*lst)->content);
		free(*lst);
		(*lst) = buf;
	}
}
