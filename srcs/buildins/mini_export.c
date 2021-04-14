/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mscot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 13:39:06 by mscot             #+#    #+#             */
/*   Updated: 2021/04/14 13:39:07 by mscot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export_line(char **line)
{
	if (line[1])
		printf("declare -x %s=\"%s\"\n", line[0], line[1]);
	else
		printf("declare -x %s\n", line[0]);
}

void	print_export(t_common *common)
{
	int	count;

	count = 0;
	while (common->env_variables_list[count])
	{
		print_export_line(common->env_variables_list[count]);
		count++;
	}
	g_errno = 0;
}

int	is_append(char *arg)
{
	if (NULL == arg || NULL == ft_strchr(arg, '='))
		return (0);
	if (*(ft_strchr(arg, '=') - 1) == '+')
		return (1);
	else
		return (0);
}

int	is_key_valid(char *key)
{
	int	count;

	count = 0;
	if (NULL == key || key[0] == '=' || ft_isdigit(key[0]))
		return (not_valid_key_return(key, count));
	while (key[count] && key[count] != '=')
	{
		if (!((ft_isalnum(key[count]) || key[count] == '_')
				|| (key[count] == '+' && key[count + 1] == '=')))
			return (not_valid_key_return(key, count));
		count++;
	}
	if (key[count] == '\0' || key[count + 1] == '\0')
		return (1);
	count++;
	while (key[count])
	{
		if (ft_strchr("()<;|`", key[count]))
			return (not_valid_key_return(key, count));
		count++;
	}
	return (1);
}

void	mini_export(t_common *common, char **simple_command)
{
	char	**key_value;
	int		count;

	count = 1;
	if (NULL == simple_command[1])
		print_export(common);
	else
	{
		while (simple_command[count])
		{
			if (is_key_valid(simple_command[count]))
			{
				key_value = get_key_and_value(simple_command[count]);
				update_envp_var(common, key_value[0],
					key_value[1], is_append(simple_command[count]));
				free(key_value[0]);
				free(key_value[1]);
				free(key_value);
				g_errno = 0;
			}
			else
				g_errno = 1;
			count++;
		}
	}
}
