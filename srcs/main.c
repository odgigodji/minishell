#include "minishell.h"


int main(int argc, char const **argv, char const **envp)
{
	t_common	common;
	int 		count = 0;
	char 		**temp = common.env_variables;

	common.env_variables = copy_envp(envp);
		ft_putenv(temp);
		count++;
//	}
//	while (ft_parser())
//	{
//	//	pre_executer(argc, argv, envp);
//	}
	return (0);
}