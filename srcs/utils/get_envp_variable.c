#include "minishell.h"

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