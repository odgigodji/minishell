#include "minishell.h"

void	execute_preprocessing(t_common *common)
{
	t_pipe	pipe_variables;

	pipe_variables.tmpin = dup(STDIN_FILENO);
	pipe_variables.tmpout = dup(STDOUT_FILENO);

	execute_processor(common, &pipe_variables);

	dup2(pipe_variables.tmpin, STDIN_FILENO);
	dup2(pipe_variables.tmpout, STDOUT_FILENO);
	close(pipe_variables.tmpin);
	close(pipe_variables.tmpout);
}

void	execute_processor(t_common *common, t_pipe *pipe_variables)
{
	int					ret;
	int					command_table_count;
	t_simple_command	*command;

	command_table_count = 0;
	pipe_variables->fdin = dup(pipe_variables->tmpin);			// input
	pipe_variables->fdpipe[0] = dup(pipe_variables->tmpin);		// input

	while (common->command.simple_commands[command_table_count])
	{
		command = common->command.simple_commands[command_table_count];

		// выбираем откуда читать
		simple_command_in_out_fd(command->infiles, pipe_variables, IS_READ, command->is_cat);
		dup2(pipe_variables->fdin, STDIN_FILENO);
		//


		// выбираем куда вести запись
		if (NULL == common->command.simple_commands[command_table_count + 1]) // если последняя команда
			pipe_variables->fdpipe[1] = pipe_variables->tmpout;
		else
			pipe(pipe_variables->fdpipe);
		simple_command_in_out_fd(command->outfiles, pipe_variables, IS_WRITE, command->is_cat);
		dup2(pipe_variables->fdout, STDOUT_FILENO);
		//

		if (is_buildin(common->command.simple_commands[command_table_count]))
			execute_simple_command_buildin(common, common->command.simple_commands[command_table_count]);
		else if (0 == (ret = fork()))							// Create child process
			execute_simple_command(common, common->command.simple_commands[command_table_count]);
		command_table_count++;
		waitpid(ret, NULL, WUNTRACED);
	}
	waitpid(ret, NULL, WUNTRACED);
}
