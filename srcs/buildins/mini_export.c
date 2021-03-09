#include "minishell.h"

int		env_list_length(t_common *common)
{
	int		count;
	char	***env_p;

	count = 0;
	env_p = common->env_variables_list;
	while (env_p[count])
		count++;
	return (count);
}

void	mini_export(t_common *common, char **simple_command)
{
	int		env_list_len;
	int 	count;
	char	***env_copy;
	int		var_index;

	env_list_len = env_list_length(common);
	if (-1 == (var_index = get_envp_var_index(common, "")))
		return ;
	if (NULL == (env_copy = malloc(sizeof(char **) * (env_list_len + 2))))
		return ;
	count = 0;
	while (common->env_variables_list[count])
	{
		env_copy[count] = common->env_variables_list[count];
		count++;
	}
}