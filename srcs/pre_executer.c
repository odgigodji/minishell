#include "minishell.h"

/*
** Функция которая исполняет команду в форке
*/

void	fork_execution(char **command, char **envp)
{
	char	**path;
	int		count;
	char	link[1000];

	int	pid;
	int rv;

	pid = fork();
	wait(&rv);
	if (pid == 0)
	{
		count = 0;
		link[0] = '\0';
		while (ft_strncmp(envp[count], "PATH", 4))
			count++;
		path = ft_split(envp[count], ':');
		count = 0;
		while (path[count])
		{
			ft_strlcat(link, path[count], 1000);
			ft_strlcat(link, "/", 1000);
			ft_strlcat(link, command[0], 1000);
			printf("[%d]	%s\n", count, link);
			execve(link, command, envp);
			count++;
			link[0] = '\0';
		}
	}
}

void	pre_executer(int argc, char **argv, char **envp)
{
	int count;

	count = 0;
	while (ft_strncmp(envp[count], "PATH", 4))
		count++;
//	char* command[]={"ls", "-l", "-a", "-G", NULL};
	char* command[]={"cat", "-e", "file", NULL};
	fork_execution(command, envp);
	printf("|-->\ntest\n");
}
