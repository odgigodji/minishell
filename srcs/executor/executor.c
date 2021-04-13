#include "minishell.h"

void	close_fd(t_pipe *pipe_variables)
{
	close(pipe_variables->tmpin);
	close(pipe_variables->tmpout);
	close(pipe_variables->fdin);
	close(pipe_variables->fdout);
	close(pipe_variables->fdpipe[0]);
	close(pipe_variables->fdpipe[1]);
}

int	is_valid_command_table(t_common *common)
{
	if (NULL != common->command.simple_commands[0]
		&& ((NULL != common->command.simple_commands[0]->arguments
			&& NULL != common->command.simple_commands[0]->arguments[0])
			|| (NULL != common->command.simple_commands[0]->infiles
			&& NULL != common->command.simple_commands[0]->infiles[0])
			   || (NULL != common->command.simple_commands[0]->outfiles
				   && NULL != common->command.simple_commands[0]->outfiles[0])))
		return (1);
	return (0);
}

void	executor(t_common *common)
{
	if (is_valid_command_table(common))
		execute_preprocessing(common);
}
