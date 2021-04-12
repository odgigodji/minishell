//
// Created by Mariam Scot on 3/10/21.
//

#include "minishell.h"

int		is_buildin(t_simple_command *simple_command)
{
	char	*list[9];
	int 	count;

	ft_bzero(list, 9);
	list[0] = "cd";
	list[1] = "pwd";
	list[2] = "echo";
	list[3] = "env";
	list[4] = "export";
	list[5] = "unset";
	list[6] = "exit";
	list[7] = "hello";
	list[8] = NULL;
	count = 0;
	while (simple_command->arguments && simple_command->arguments[0] && list[count])
	{
		if (!strncmp(list[count], simple_command->arguments[0], ft_strlen(list[count]) + 1))
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
	else if (!ft_strncmp("exit", simple_command->arguments[0], 5))
		mini_exit(common);
	else if (!ft_strncmp("hello", simple_command->arguments[0], 6))
		mini_hello();
}

void	execute_simple_command(t_common *common, t_simple_command *simple_command, t_pipe *pipe_variables)
{
	char	**path;
	char	**temp_envp;
	int 	count;
	char	command[MAX_PATH];

	temp_envp = make_envp(common);
	path = split_path(common);
	count = 0;
	command[0] = '\0';
	close_fd(pipe_variables);
	execve(simple_command->arguments[0], simple_command->arguments, temp_envp);
	while (path && path[count])
	{
		ft_strlcat(command, path[count], MAX_PATH);
		ft_strlcat(command, "/", MAX_PATH);
		ft_strlcat(command, simple_command->arguments[0], MAX_PATH);
		execve(command, simple_command->arguments, temp_envp);
		count++;
		command[0] = '\0';
	}
	errno = 1;
//	free_argument_list(&temp_envp);		// fixme не влияет на утечки
//	free_argument_list(&path);			// fixme не влияет на утечки
	printf("%s: command not found: %s\n", SHELL_NAME, simple_command->arguments[0]);
	exit(1);
}