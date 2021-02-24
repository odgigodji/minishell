#include "minishell.h"


int main(int argc, char const **argv, char const **envp)
{
	t_common	common;

	common.env_variables = copy_envp(envp);
	while (ft_parser(&common))
	{
		executor(common);
	}
	return (0);
}