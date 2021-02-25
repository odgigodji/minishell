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
		link[0] = '\0';
		path = split_path(envp);
		count = 0;
		while (path[count])
		{
			ft_strlcat(link, path[count], 1000);
			ft_strlcat(link, "/", 1000);
			ft_strlcat(link, command[0], 1000);
//			printf("[%d]	%s\n", count, link);
			execve(link, command, envp);
			count++;
			link[0] = '\0';
		}
	}
}

void	pre_executor(int argc, char **argv, char **envp)
{
	int count;

	count = 0;
	while (ft_strncmp(envp[count], "PATH", 4))
		count++;
	char *command_ls[] = {"ls", "-a", "-G", NULL};
	char *command_cat[] = {"cat", "-e", "file", NULL};
	char ***command_table = malloc(sizeof(char **) * 3);

	command_table[0] = command_ls;
	command_table[1] = command_cat;
	command_table[2] = NULL;
	fork_execution(command_table[0], envp);
//	printf("|-->\ntest\n");
}
