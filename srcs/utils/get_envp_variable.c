#include "minishell.h"

/*
** возвращает содержимое переменной var из envp или (null) если такой строки нет
*/

char	*get_envp_variable(t_common *common, char *var)
{
	int		count;

	count = 0;
	while (common->env_variables[count])
	{
		if (!ft_strncmp(common->env_variables[count], var, ft_strlen(var))
			&& common->env_variables[count][ft_strlen(var)] == '=')
			break ;
		count++;
		if (NULL == common->env_variables[count])
			return (NULL);
	}
	return (ft_strrchr(common->env_variables[count], '=') + 1);
}

char	*get_envp_variable_from_char(char **envp, char *var)
{
	int		count;

	count = 0;
	while (envp[count])
	{
		if (!ft_strncmp(envp[count], var, ft_strlen(var))
			&& envp[count][ft_strlen(var)] == '=')
			break ;
		count++;
		if (NULL == envp[count])
			return (NULL);
	}
	return (ft_strrchr(envp[count], '=') + 1);
}

/*
** первращает строку типа "USER=mscot" в массив [["USER"], ["mscot"]]
*/

char	**get_key_value(char *envp_line)
{
	char	**var;
	int		key_len;
	int		append_flag;

	if (NULL == (var = malloc(sizeof(char *) * 3)))
		return (NULL);
	append_flag = 0;
	key_len = (int)(ft_strchr(envp_line, '=') - envp_line);
	if (envp_line[key_len - 1] == '+')
		append_flag = 1;
	var[0] = ft_substr(envp_line, 0, key_len - append_flag);
	var[1] = ft_substr(envp_line, key_len + 1, ft_strlen(envp_line) - key_len);
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
	if (NULL == (result = malloc(sizeof(char **) * list_length + 1)))
		return (NULL);
	result[list_length] = NULL;
	count = 0;
	while (envp[count])
	{
		result[count] = get_key_value(envp[count]);
		count++;
	}
	return (result);
}

/*
** возвращает строку из envp начинающуюся с line или (null) если такой строки нет
*/

char	*get_envp_line(t_common *common, char *line)
{
	int		count;

	count = 0;
	while (common->env_variables[count])
	{
		if (!ft_strncmp(common->env_variables[count], line, ft_strlen(line))
			&& common->env_variables[count][ft_strlen(line)] == '=')
			break ;
		count++;
		if (NULL == common->env_variables[count])
			return (NULL);
	}
	return (common->env_variables[count]);
}

/*
** возвращает индекс переменой в списке (char ***) envp
** или -1 если такой переменной нет
*/

int		get_envp_var_index(t_common *common, char *var)
{
	int	count;

	count = 0;
	while (common->env_variables_list[count])
	{
		if (!ft_strncmp(common->env_variables_list[count][0], var, ft_strlen(var) + 1))
			return (count);
		count++;
	}
	return (-1);
}

char	*get_envp_var_pointer(t_common *common, char *var)
{
	int	count;
	int count_index;

	count = 0;
	count_index = 0;
	while (var[count_index] && var[count_index] != '=')
		count_index++;
	while (common->env_variables_list[count])
	{
		if (!ft_strncmp(common->env_variables_list[count][0], var, count_index + 1))
			return (common->env_variables_list[count][1]);
		count++;
	}
	return (NULL);
}

int		args_list_len(char	***arg_list)
{
	int	count;

	count = 0;
	while (arg_list[count])
		count++;
	return (count);
}

void	free_arg_list(char ****arg_list)
{
	int count;
	int arg_count;

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
** выделение копирование с выделением памяти списка char ***
** и занесением нового аргумента в список
** память выделяется на len + 2 аргументов для нового аргумента
*/

char	***add_argument(t_common *common, char *new_key, char *new_value)
{
	char	***result;
	int		count;

	if (NULL == (result = malloc(sizeof(char **) * (args_list_len(common->env_variables_list) + 2))))
		return (NULL);
	count = 0;
	while (common->env_variables_list[count])
	{
		result[count] = common->env_variables_list[count];
		count++;
	}
	result[count] = malloc(sizeof(char **) * 3);
	result[count][0] = ft_strdup(new_key);
	result[count][1] = ft_strdup(new_value);
	result[count][2] = NULL;
	result[count + 1] = NULL;
//	free(common->env_variables_list);
	common->env_variables_list = result;
	return (result);
}

/*
** назначение нового значения переменной в список char ***
*/

int		update_envp_var(t_common *common, char *key, char *new_value, int append)
{
	int		index;
	char	*temp;

	index = get_envp_var_index(common, key);
	if (-1 != index)
	{
		if (append)
		{
			temp = common->env_variables_list[index][1];
			common->env_variables_list[index][1] = ft_strjoin(common->env_variables_list[index][1], new_value);
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
		puts("arg");
		add_argument(common, key, new_value);
		return (0);
	}
}