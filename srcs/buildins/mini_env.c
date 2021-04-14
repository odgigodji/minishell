/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mscot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 13:38:43 by mscot             #+#    #+#             */
/*   Updated: 2021/04/14 13:38:45 by mscot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_env(t_common *common)
{
	int		count;

	count = 0;
	while (common->env_variables_list[count])
	{
		if (common->env_variables_list[count][1])
			printf("%s=%s\n", common->env_variables_list[count][0],
				common->env_variables_list[count][1]);
		count++;
	}
	g_errno = 0;
}
