#include <minishell.h>


int main(int argc, char const **argv, char const **envp)
{
	t_common	common;

	common.env_variables = copy_envp(envp);

	char **temp = common.env_variables;
	int count = 0;
	while (temp)
	{
		printf("[%d] %s\n", count, temp[count]);
		count++;
	}
//	printf("hello");
//	char *line;
	while (ft_parser())
	{
	//	pre_executer(argc, argv, envp);
	}
	return (0);
}