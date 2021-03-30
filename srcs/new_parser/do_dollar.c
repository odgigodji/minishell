#include "minishell.h"

void ft_print_env(t_common *common, char **env_variables)
{
	int i = 0;

	while(env_variables[i])
	{
		if (DEB_DOLLAR)
		printf(YEL"|%s|\n"RESET, env_variables[i]);
		i++;
	}
}


int ft_do_dollar(t_common *common, char *line)
{

	printf(GRN"dollar\n"RESET);
	ft_print_env(common, common->env_variables);
	return (0);
}
