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

void	print_export(t_common *common)
{
	int	count;

	count = 0;
//	puts(GRN "test" RESET);

	printf("declare -x %s=\"%s\"\n", common->env_variables_list[count][0], common->env_variables_list[count][1]);
	while (common->env_variables_list[count])
	{
		printf("declare -x %s=\"%s\"\n", common->env_variables_list[count][0], common->env_variables_list[count][1]);
		count++;
	}
//	puts(GRN "test" RESET);
}

int		is_append(char *arg)
{
	if (NULL == arg)
		return (0);
	if (*(ft_strchr(arg, '=') - 1) == '+')
		return (1);
	else
		return (0);
}

void	mini_export(t_common *common, char **simple_command)
{
	char	**key_value;
	int		count;

	count = 1;
	if (NULL == simple_command[1])
	{
//		puts(RED "test" RESET);
		print_export(common);
		return ;
	}
	else
	{
		while (simple_command[count])
		{
			key_value = get_key_value(simple_command[count]);
			update_envp_var(common, key_value[0], key_value[1], is_append(simple_command[count]));
			free(key_value[0]);
			free(key_value[1]);
			count++;
		}
	}
}