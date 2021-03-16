//
// Created by Mariam Scot on 3/16/21.
//
#include "minishell.h"

void	mini_unset(t_common *common, char **keys)
{
	int		count;
	int		count_keys;
	char	**temp;
	int		flag;

	count = 0;
	flag = 0;
	count_keys = 1;
	while (keys[count_keys])
	{
		while (common->env_variables_list[count])
		{
			if (!ft_strncmp(common->env_variables_list[count][0], keys[count_keys], ft_strlen(keys[count_keys]) + 1))
			{
				temp = common->env_variables_list[count];
				free(temp[0]);
				free(temp[1]);
				free(temp);
				flag = 1;
			}
			if (flag)
				common->env_variables_list[count] = common->env_variables_list[count + 1];
			count++;
		}
		common->env_variables_list[count] = NULL;
		flag = 0;
		count = 0;
		count_keys++;
	}
}