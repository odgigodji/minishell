//
// Created by Mariam Scot on 3/10/21.
//

#include "executor_tests.h"

void	test_get_envp_var_pointer(t_common *common, char **envp)
{
	int		count;
	int 	count_copy;
	char	temp[100];
	int		count_test;

	count = 0;
	count_test = 0;
	printf ("%3s ", "01");
	while (envp[count])
	{
		count_copy = 0;
		ft_bzero(temp, 100);
		while (envp[count] && envp[count][count_copy] != '=')
		{
			temp[count_copy] = envp[count][count_copy];
			count_copy++;
		}
		if (ft_strncmp(ft_strrchr(envp[count], '=') + 1, get_envp_var_pointer(common, temp), 100))
		{
			count_test++;
			printf("[%d][%s] [%s]\n", count, envp[count], common->env_variables_list[count][1]);
		}
		count++;
	}
	if (count_test == 0)
		printf("[" GRN "ok" RESET "] test_get_envp_var_pointer\n");
	else
		printf("[" RED "ng" RESET "] test_get_envp_var_pointer\n");
}