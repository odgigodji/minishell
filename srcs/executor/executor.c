#include "minishell.h"

void	executor(t_common common)
{
	fork_execution(common.command.simple_commands_struct->arguments, common.env_variables);
}