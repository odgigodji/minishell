#include "minishell.h"

void ft_print_env(t_common *common, char **env_variables, char ***env_variables_list, char *res)
{
	int i = 0;
	int j = 0;
	char *ret = ft_calloc(sizeof(char), 50);
	while(env_variables_list[i])
	{
		while(env_variables_list[i][j])
		{
			if (DEB_DOLLAR)
				printf(YEL"|%s|\n"RESET, env_variables_list[i][j]);
			j++;
		}
		i++;
	}
	ret = get_envp_var_pointer(common, res);
	printf(RED"|%s|\n"RESET, ret);
}


int ft_do_dollar(t_common *common, char *line)
{
	printf(GRN"dollar\n"RESET);
	char res[10] = "SHELL";
	ft_print_env(common, common->env_variables, common->env_variables_list, res);
	return (0);
}
