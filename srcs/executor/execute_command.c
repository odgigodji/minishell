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
	list[3] = "env";
	list[4] = "export";
	list[5] = "unset";
	list[6] = "exit";
	list[7] = NULL;
	count = 0;
	while (list[count])
	{
		if (!strncmp(list[count], simple_command->arguments[0], 100))
			return (1);
		count++;
	}
	return (0);
}

void	execute_simple_command_buildin(t_common *common, t_simple_command *simple_command)
{
//	printf(YEL "DEBUG: не системная функция mini_%s:\n"RESET, simple_command->arguments[0]);
	if (!ft_strncmp("cd", simple_command->arguments[0], 3))
		mini_cd(simple_command->arguments, common);
	else if (!ft_strncmp("pwd", simple_command->arguments[0], 4))
		mini_pwd(common);
	else if (!ft_strncmp("echo", simple_command->arguments[0], 5))
		mini_echo(simple_command->arguments);
	else if (!ft_strncmp("env", simple_command->arguments[0], 4))
		mini_env(common);
	else if (!ft_strncmp("export", simple_command->arguments[0], 7))
		mini_export(common, simple_command->arguments);
	else if (!ft_strncmp("unset", simple_command->arguments[0], 6))
		mini_unset(common, simple_command->arguments);
	else if (!ft_strncmp("exit", simple_command->arguments[0], 6))
		mini_exit(common);
}

void	execute_simple_command(t_common *common, t_simple_command *simple_command)
{
	char	**path;
	char	**temp_envp;
	int 	count;
	char	command[MAX_PATH];

	if (is_buildin(simple_command))
	{
		execute_simple_command_buildin(common, simple_command);
		exit(0);
	}
//	printf("");
	temp_envp = make_envp(common);
	path = split_path(common->env_variables);
	count = 0;
	command[0] = '\0';
	execve(simple_command->arguments[0], simple_command->arguments, temp_envp);
	while (path[count])
	{
		ft_strlcat(command, path[count], MAX_PATH);
		ft_strlcat(command, "/", MAX_PATH);
		ft_strlcat(command, simple_command->arguments[0], MAX_PATH);
		execve(command, simple_command->arguments, temp_envp);
		count++;
		command[0] = '\0';
	}
	errno = 1;
	perror("execve child. Command not executed (no such command?)\n");
	exit(0);
}