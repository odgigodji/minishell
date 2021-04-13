#include "minishell.h"

/*
** converts string type of "USER=mscot" into [["USER"], ["mscot"]]
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
**	Returns environment variables list type of char ***
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
** returns index of values in array (char ***) envp
** or -1 in case of absence of such variable
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
