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

void	mini_export(t_common *common, char **simple_command)
{
	int		env_list_len;
	int 	count;
	char	***env_copy;

	env_list_len = env_list_length(common);
	if (NULL == simple_command[1])
	{
//		puts(RED "test" RESET);
		print_export(common);
		return ;
	}
	if (NULL == get_envp_var_pointer(common, ""))
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