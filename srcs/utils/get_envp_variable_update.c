#include "minishell.h"

/*
** копирование с выделением памяти списка char ***
** и занесением нового аргумента в список
** память выделяется на len + 2 аргументов для нового аргумента
*/

char	***add_argument(t_common *common, char *new_key, char *new_value)
{
	char	***result;
	int		count;

	result = malloc(
			sizeof(char **) * (args_list_len(common->env_variables_list) + 2));
	if (NULL == result)
		return (NULL);
	count = 0;
	while (common->env_variables_list[count])
	{
		result[count] = common->env_variables_list[count];
		count++;
	}
	result[count] = malloc(sizeof(char **) * 3);
	result[count][0] = ft_strdup(new_key);
	if (new_value)
		result[count][1] = ft_strdup(new_value);
	else
		result[count][1] = NULL;
	result[count][2] = NULL;
	result[count + 1] = NULL;
	free(common->env_variables_list);
	common->env_variables_list = result;
	return (result);
}

/*
** назначение нового значения переменной в список char ***
*/

int	update_envp_var(t_common *common,
					   char *key,
					   char *new_value,
					   int append)
{
	int		index;
	char	*temp;

	index = get_envp_var_index(common, key);
	if (-1 != index)
	{
		if (append)
		{
			temp = common->env_variables_list[index][1];
			common->env_variables_list[index][1] = ft_strjoin(
					common->env_variables_list[index][1], new_value);
			free(temp);
		}
		else
		{
			free(common->env_variables_list[index][1]);
			common->env_variables_list[index][1] = ft_strdup(new_value);
		}
		return (1);
	}
	else
	{
		add_argument(common, key, new_value);
		return (0);
	}
}
