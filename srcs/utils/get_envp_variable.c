#include "minishell.h"

/*
** первращает строку типа "USER=mscot" в массив [["USER"], ["mscot"]]
*/

char	**get_key_and_value(char *envp_line)
{
	char	**var;
	int		key_len;
	int		append_flag;

	var = malloc(sizeof(char *) * 3);
	if (NULL == envp_line || NULL == var)
		return (NULL);
	append_flag = 0;
	if (ft_strchr(envp_line, '='))
	{
		key_len = (int)(ft_strchr(envp_line, '=') - envp_line);
		if (envp_line[key_len - 1] == '+')
			append_flag = 1;
		var[0] = ft_substr(envp_line, 0, key_len - append_flag);
		var[1] = ft_substr(envp_line, key_len + 1,
				ft_strlen(envp_line) - key_len);
	}
	else
	{
		var[0] = ft_substr(envp_line, 0, ft_strlen(envp_line));
		var[1] = NULL;
	}
	var[2] = NULL;
	return (var);
}

/*
** возвращает список переменных env в виде массива массивов строк
*/

char	***get_envp(char **envp)
{
	char	***result;
	int		count;
	int		list_length;

	list_length = list_len((const char **)envp);
	result = malloc(sizeof(char **) * (list_length + 1));
	if (NULL == result)
		return (NULL);
	count = 0;
	while (envp[count])
	{
		result[count] = get_key_and_value(envp[count]);
		if (!ft_strncmp(result[count][0], "SHLVL", 6))
		{
			free(result[count][1]);
			result[count][1] = ft_itoa(ft_atoi(result[count][1]) + 1);
		}
		count++;
	}
	result[count] = NULL;
	return (result);
}

/*
** возвращает индекс переменой в списке (char ***) envp
** или -1 если такой переменной нет
*/

int	get_envp_var_index(t_common *common, char *var)
{
	int	count;

	count = 0;
	while (common->env_variables_list[count])
	{
		if (!ft_strncmp(common->env_variables_list[count][0],
			var, ft_strlen(var) + 1))
			return (count);
		count++;
	}
	return (-1);
}

char	*get_envp_var_pointer(t_common *common, char *var)
{
	int	count;
	int	count_index;

	count = 0;
	count_index = 0;
	while (var[count_index] && var[count]
		&& (var[count] == '_' || ft_isalnum(var[count])))
		count_index++;
	while (common->env_variables_list[count])
	{
		if (!ft_strncmp(common->env_variables_list[count][0],
			var, count_index + 1))
			return (common->env_variables_list[count][1]);
		count++;
	}
	return (NULL);
}

size_t	list_len(const char **list)
{
	size_t	count;

	count = 0;
	while (list[count])
		count++;
	return (count);
}

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
