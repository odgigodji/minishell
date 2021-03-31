#include "minishell.h"

void	executor(t_common *common)
{
	execute_processor(common);
//	execute_command(common, common->env_variables);
	(*common).command = command_init();
}