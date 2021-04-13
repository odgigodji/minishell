//
// Created by Mariam Scot on 4/13/21.
//

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