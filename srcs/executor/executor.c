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

void	executor(t_common *common)
{
	execute_preprocessing(common);
}
