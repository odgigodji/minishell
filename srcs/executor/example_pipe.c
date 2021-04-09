#include "minishell.h"

void	execute_preprocessing(t_common *common)
{
	t_pipe	pipe_variables;

	pipe_variables.tmpin = dup(STDIN_FILENO);
	pipe_variables.tmpout = dup(STDOUT_FILENO);
	g_signal_process_status = 1;
	execute_processor(common, &pipe_variables);

	g_signal_process_status = 0;
	dup2(pipe_variables.tmpin, STDIN_FILENO);
	dup2(pipe_variables.tmpout, STDOUT_FILENO);
	close(pipe_variables.tmpin);
	close(pipe_variables.tmpout);

	close(pipe_variables.fdin);
	close(pipe_variables.fdout);
	close(pipe_variables.fdpipe[0]);
	close(pipe_variables.fdpipe[1]);

}

void	execute_processor(t_common *common, t_pipe *pipe_variables)
{
	int					ret;
	int					command_table_count;
	t_simple_command	*simple_command;

	command_table_count = 0;
	pipe_variables->fdpipe[0] = dup(pipe_variables->tmpin);		//	input

	while (common->command.simple_commands && common->command.simple_commands[command_table_count])
	{
		simple_command = common->command.simple_commands[command_table_count];

		//	выбираем откуда читать
		if (-1 == (simple_command_in_out_fd(simple_command->infiles, pipe_variables, IS_READ, simple_command->is_cat)))
			return ;
		close(pipe_variables->fdpipe[0]);	// fixme
		dup2(pipe_variables->fdin, STDIN_FILENO);
		close(pipe_variables->fdin);		// fixme
		//


		//	выбираем куда вести запись
		if (NULL == common->command.simple_commands[command_table_count + 1])	//	если последняя команда
		{
			pipe_variables->fdpipe[1] = dup(pipe_variables->tmpout);
		}
		else
			pipe(pipe_variables->fdpipe);
		if (-1 == (simple_command_in_out_fd(simple_command->outfiles, pipe_variables, IS_WRITE, simple_command->is_cat)))
			return ;
		close(pipe_variables->fdpipe[1]);	//	fixme
		dup2(pipe_variables->fdout, STDOUT_FILENO);
		close(pipe_variables->fdout);		//	fixme
		//


		//	выполняем команду

		if (is_buildin(common->command.simple_commands[command_table_count]))
			execute_simple_command_buildin(common, simple_command);
		else if (0 == (ret = fork()))											//	создаём дочерний процесс
		{
			if (simple_command->arguments && simple_command->arguments[0])
			{
				execute_simple_command(common, simple_command);
			}
		}
//		else
//		{
//			wait(NULL);
//		}
//		waitpid(ret, NULL, WUNTRACED);
//		waitpid(ret, NULL, WNOHANG);	// сигналы работают
//		waitpid(ret, NULL, 0);
		command_table_count++;
	}
	while (command_table_count && command_table_count--)
		wait(NULL);
}
