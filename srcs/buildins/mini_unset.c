#include "minishell.h"

int	mini_unset_a_var(char ***var_list, char *key)
{
	int		count;
	char	**temp;
	int		flag;

	count = 0;
	flag = 0;
	if (!is_key_valid(key))
		return (-1);
	while (var_list[count])
	{
		if (!ft_strncmp(var_list[count][0],
			key, ft_strlen(key) + 1))
		{
			temp = var_list[count];
			free(temp[0]);
			free(temp[1]);
			free(temp);
			flag = 1;
		}
		if (flag)
			var_list[count] = var_list[count + 1];
		count++;
	}
	var_list[count] = NULL;
	return (flag);
}

void	mini_unset(t_common *common, char **keys)
{
	int		count_keys;

	count_keys = 1;
	while (keys[count_keys])
	{
		mini_unset_a_var(common->env_variables_list, keys[count_keys]);
		count_keys++;
	}
	g_errno = 0;
}
