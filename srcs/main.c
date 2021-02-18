#include <minishell.h>

int main(int argc, char const **argv, char const **envp)
{
//	printf("hello");
	char *line;

	ft_putstr_fd("\033[35mminishell$ \033[0m", 0);
	get_next_line(1, &line);
	printf("%s", line);
//	pre_executer(argc, argv, envp);
	return (0);
}