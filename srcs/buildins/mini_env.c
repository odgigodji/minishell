#include "minishell.h"

void	mini_env(t_common *common)
{
	int		count;

	count = 0;
	while (common->env_variables_list[count])
	{
		if (common->env_variables_list[count][1])
			printf("%s=%s\n", common->env_variables_list[count][0], common->env_variables_list[count][1]);
		count++;
	}
}