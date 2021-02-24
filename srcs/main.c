#include "minishell.h"


int main(int argc, char const **argv, char const **envp)
{
	t_common	common;

	while (ft_parser(&common))
	{
		executor(common);
	}
	return (0);
}