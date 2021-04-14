/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mscot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 13:38:54 by mscot             #+#    #+#             */
/*   Updated: 2021/04/14 13:38:56 by mscot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_exit(t_common *common)
{
	free_arg_list(&(common->env_variables_list));
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	write(1, "\a", 1);
	exit(g_errno);
}
