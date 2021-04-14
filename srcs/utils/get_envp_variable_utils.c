/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp_variable_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mscot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 13:53:33 by mscot             #+#    #+#             */
/*   Updated: 2021/04/14 13:53:34 by mscot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	args_list_len(char	***arg_list)
{
	int	count;

	count = 0;
	while (arg_list[count])
		count++;
	return (count);
}

int	ft_array_len(char	**arg_list)
{
	int	count;

	count = 0;
	while (arg_list[count])
		count++;
	return (count);
}

size_t	list_len(const char **list)
{
	size_t	count;

	count = 0;
	while (list[count])
		count++;
	return (count);
}

void	free_arg_list(char ****arg_list)
{
	int	count;
	int	arg_count;

	count = 0;
	arg_count = 0;
	while ((*arg_list)[count])
	{
		while ((*arg_list)[count][arg_count])
		{
			free((*arg_list)[count][arg_count]);
			arg_count++;
		}
		free((*arg_list)[count]);
		count++;
	}
	free(*arg_list);
}
