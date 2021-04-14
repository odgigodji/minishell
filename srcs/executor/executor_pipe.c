/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mscot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 13:41:08 by mscot             #+#    #+#             */
/*   Updated: 2021/04/14 14:18:30 by mscot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_preprocessing(t_common *common)
{
	t_pipe	pipe_variables;

	pipe_variables.tmpin = dup(STDIN_FILENO);
	pipe_variables.tmpout = dup(STDOUT_FILENO);
	execute_processor(common, &pipe_variables);
	dup2(pipe_variables.tmpin, STDIN_FILENO);
	dup2(pipe_variables.tmpout, STDOUT_FILENO);
	close_fd(&pipe_variables);
}

int	switch_stdin(t_simple_command *simple_command, t_pipe *pipe_variables)
{
	if (-1 == (simple_command_in_out_fd(simple_command->infiles,
				pipe_variables, IS_READ,
				simple_command->is_cat)))
		return (1);
	close(pipe_variables->fdpipe[0]);
	dup2(pipe_variables->fdin, STDIN_FILENO);
	close(pipe_variables->fdin);
	return (0);
}

int	switch_stdout(t_simple_command *simple_command,
				t_simple_command *next_simple_command,
				t_pipe *pipe_variables)
{
	if (NULL == next_simple_command)
		pipe_variables->fdpipe[1] = dup(pipe_variables->tmpout);
	else
		pipe(pipe_variables->fdpipe);
	if (-1 == (simple_command_in_out_fd(simple_command->outfiles,
				pipe_variables, IS_WRITE,
				simple_command->is_cat)))
		return (1);
	close(pipe_variables->fdpipe[1]);
	dup2(pipe_variables->fdout, STDOUT_FILENO);
	close(pipe_variables->fdout);
	return (0);
}

int	execute_simple_command_processor(t_simple_command *simple_command,
									 t_pipe *pipe_variables,
									 t_common *common)
{
	int	pid;

	pid = 0;
	if (is_buildin(simple_command))
		execute_simple_command_buildin(common, simple_command);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (simple_command->arguments && simple_command->arguments[0])
				execute_simple_command(common, simple_command, pipe_variables);
		}
	}
	return (pid);
}

void	execute_processor(t_common *common, t_pipe *pipe_variables)
{
	int					command_table_count;
	t_simple_command	*simple_command;
	int					ret;
	int					count;

	count = 1;
	command_table_count = 0;
	pipe_variables->fdpipe[0] = dup(pipe_variables->tmpin);
	while (common->command.simple_commands
		&& common->command.simple_commands[command_table_count])
	{
		simple_command = common->command.simple_commands[command_table_count];
		switch_stdin(simple_command, pipe_variables);
		switch_stdout(simple_command,
			common->command.simple_commands[command_table_count + 1],
			pipe_variables);
		ret = execute_simple_command_processor(simple_command,
				pipe_variables, common);
		command_table_count++;
	}
	while (count > 0)
		count = wait(&g_errno);
}
