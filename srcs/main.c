#include <minishell.h>

int main(int argc, char const **argv, char const **envp)
{
//	printf("hello");
//	char *line;

	ft_putstr_fd("\033[35mminishell$ \033[0m", 0);
	ft_parser();
//	pre_executer(argc, argv, envp);
	return (0);
}