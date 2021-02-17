#include "minishell.h"

void	pre_executer(int argc, char **argv, char **envp)
{
	char	**test;
	char	*ls = "/ls";
	char	*key = "-l";
	int		count = 0;
	char	**path;
	char	*command;
	int		len;

	path = ft_split(envp[0], ':');
	while (path[count])
		printf("[%d] |%s|\n", count, path[count++]);
	count = 0;

	len = (int)ft_strlen(path[count]) + (int)ft_strlen(ls) + 1;
	command = malloc(len);
	*command = '\0';
	int	check;
	while (path)
	{
		ft_strlcat(command, path[count], (len));
		ft_strlcat(command, ls, (len));
		check = execve(command, argv, envp);
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[%d] %s\n", check, command);
//		printf("[%d] %s\n", count, command[count++]);
		command[0] = '\0';
		path++;
	}
}

//	pre_executer(argc, argv, envp);
//int count;
//
//count = 0;
//while (!ft_strncmp(envp[count], "PATH", 4))
//count++;
//printf("{%s}\n", envp[count]);
////	char* arglist[]={"/bin/ls", "-a", "-G", "-l", NULL};
//char* arglist[]={"/bin/echo", envp[count], NULL};
//execve(arglist[0], arglist, envp);