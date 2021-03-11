#include "minishell.h"

void	mini_env(t_common *common)
{
	int	count;

	count = 0;
	while (common->env_variables_list[count])
	{

		count++;
	}
}