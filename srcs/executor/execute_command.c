//
// Created by Mariam Scot on 3/10/21.
//

#include "minishell.h"

int		is_buildin(t_simple_command *simple_command)
{
	char	*list[8];
	int 	count;

	ft_bzero(list, 8);
	list[0] = "cd";
	list[1] = "pwd";
	list[2] = "echo";
//	list[3] = "export";
//	list[4] = "unset";
//	list[5] = "env";
//	list[6] = "exit";
	count = 0;
	while (list[count])
	{
		if (!ft_strncmp(list[count], simple_command->arguments[0], 100))
			return (1);
		count++;
	}
	return (0);
}

void	execute_simple_command_buildin(t_common *common, t_simple_command *simple_command)
{
	if (!ft_strncmp("cd", simple_command->arguments[0], 3))
	{
		printf(YEL "DEBAG: " RESET "не системная функция mini_cd\n");
		mini_cd(simple_command->arguments, common);
	}
	else if (!ft_strncmp("pwd", simple_command->arguments[0], 3))
	{
		printf(YEL "DEBAG: " RESET "не системная функция mini_pwd\n");
		mini_pwd(common->env_variables);
	}
	else if (!ft_strncmp("echo", simple_command->arguments[0], 3))
	{
		printf(YEL "DEBAG: " RESET "не системная функция mini_echo\n");
		mini_echo(simple_command->arguments);
	}
}

void	execute_simple_command(t_common *common, t_simple_command *simple_command)
{
	char	**path;
	int 	count;
	char	command[100];

	if (is_buildin(simple_command))
	{
		execute_simple_command_buildin(common, simple_command);
		return ;
	}
	path = split_path(common->env_variables);
	count = 0;
	command[0] = '\0';
	while (path[count])
	{
		ft_strlcat(command, path[count], 100);
		ft_strlcat(command, "/", 100);
		ft_strlcat(command, simple_command->arguments[0], 100);
		execve(command, simple_command->arguments, common->env_variables);
		count++;
		command[0] = '\0';
	}
	errno = 0;
	perror("execve child. Command not executed (no such command?)\n");
	exit(0);
}