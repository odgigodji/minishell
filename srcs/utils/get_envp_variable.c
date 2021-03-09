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

char	**get_var(char *envp_line)
{
	char	**var;
	int		var_name_len;

	if (NULL == (var = malloc(sizeof(char *) * 3)))
		return (NULL);
	var_name_len = (int)(ft_strchr(envp_line, '=') - envp_line);
	var[0] = ft_substr(envp_line, 0, var_name_len);
	var[1] = ft_substr(envp_line, var_name_len + 1, ft_strlen(envp_line) - var_name_len);
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
		result[count] = get_var(envp[count]);
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

int		update_envp_var(t_common *common, char *var, char *new_value)
{
	int	index;

	index = get_envp_var_index(common, var);
	if (-1 != index)
	{
		free(common->env_variables_list[index][1]);
		common->env_variables_list[index][1] = new_value;
		return (1);
	}
	else
		return (0);
}