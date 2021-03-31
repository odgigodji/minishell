#include "minishell.h"

void	pipe_init(t_pipe *pipe_variables, t_simple_command *command)
{
	int	count;
	int fd;

	count = 0;
//	if (NULL == command->infile[0])												//	if (infile)
		pipe_variables->fdin = dup(pipe_variables->tmpin);	// use default input		//	используем стандартный ввод
//		pipe_variables->fdin = pipe_variables->fdpipe[0];		//	read fd назначаем на in
//	else
	if (NULL != command->infile[0])
		while (command->infile[count])
		{
			if (-1 == (fd = open(command->infile[count], O_RDONLY)))
			{
				ft_putstr_fd("minishell: ", 1);
				ft_putstr_fd(command->infile[count], 1);
				ft_putstr_fd(": No such file or directory(pipe_init)", 1);
				count++;
				continue ;
			}
			pipe_variables->fdin = fd;
			count++;
			if (command->infile[count])
				close(pipe_variables->fdin);
		}
}
//restore in/out defaults
void	restore_default_in_out_puts(t_pipe *pipe_variables)
{
	dup2(pipe_variables->tmpin, STDIN_FILENO);
	dup2(pipe_variables->tmpout, STDOUT_FILENO);
	close(pipe_variables->tmpin);
	close(pipe_variables->tmpout);
}

int	do_a_pipe(t_pipe *pipe_variables, t_simple_command *command)
{
	int fd;

	// create pipe
	pipe(pipe_variables->fdpipe);							//	создаём pipe
	if (NULL == command->outfile[0])
	{
		pipe_variables->fdout = pipe_variables->fdpipe[1];        //	write fd назначаем на out
		return (pipe_variables->fdpipe[1]);
	}
	else
	{
		fd = simple_command_in_out_fd(command->outfile, pipe_variables, IS_WRITE, command->is_cat);
		if (-1 == fd)
			return (1);
		pipe_variables->fdout = fd;
		return (fd);
	}
}

void	last_simple_command_output(t_pipe *pipe_variables, t_simple_command *command)
{
	int	fd;
	int	count;
//	if (NULL != common->command.out_file)	//	if (outfile)
//		pipe_variables->fdout = open(*common->command.out_file, O_WRONLY, O_APPEND);
//	else
	count = 0;
	pipe_variables->fdout = dup(pipe_variables->tmpout);	//	то назначаем stdout (сохранённый ранее), результат вывода будем писать в стандартный вывод
	if (NULL != command->outfile[0])
	{
		while (command->outfile[count])
		{
			if (-1 == (fd = open(command->outfile[count], O_WRONLY | O_APPEND | O_TRUNC | O_CREAT, 0644)))
			{
				ft_putstr_fd("minishell: ", 1);
				ft_putstr_fd(command->outfile[count], 1);
				ft_putstr_fd(": No such file or directory(last_write)\n", 1);
				count++;
				continue;
			}
			pipe_variables->fdout = fd;
			count++;
			if (command->outfile[count])
				close(pipe_variables->fdout);
		}
	}
	pipe_variables->fdin = pipe_variables->fdpipe[0];		//	read fd назначаем на in
	 count = 0;
	if (NULL != command->infile[0])
	{
		while (command->infile[count])
		{
			if (-1 == (fd = open(command->infile[count], O_RDONLY)))
			{
				ft_putstr_fd("minishell: ", 1);
				ft_putstr_fd(command->infile[count], 1);
				ft_putstr_fd(": No such file or directory(lasl_read)\n", 1);
				count++;
				continue;
			}
			pipe_variables->fdin = fd;
			count++;
			if (command->infile[count])
				close(pipe_variables->fdin);
		}
	}
}

//void	execute_command(t_common *common, char **envp)
//{
//	int		command_table_len = common->command.num_of_simple_commands;	//	возможно number_of_available_simple_commands
//	int		command_table_count = 0;
//	int		ret;
//	t_pipe	pipe_variables;
//
//	pipe_variables.tmpin = dup(STDIN_FILENO);		//	save in
//	pipe_variables.tmpout = dup(STDOUT_FILENO);		//	save out
//
//	pipe_init(&pipe_variables, common->command.simple_commands[command_table_count]);		// сохраняем stdin/stdout определяем откуда
//	while (common->command.simple_commands[command_table_count])
//	{
//		dup2(pipe_variables.fdin, STDIN_FILENO);			// подменяем stdin (fd = 0) на ранее созданный fdin
//		close(pipe_variables.fdin);
//		if (command_table_count == command_table_len - 1)	//	если это последняя simple_command
//		{
//			last_simple_command_output(&pipe_variables, common->command.simple_commands[command_table_count]);
//		}
//		else												//	иначе // not last simple command
//		{
//			do_a_pipe(&pipe_variables, common->command.simple_commands[command_table_count]);
//		}
//		//	Redirect output
//		dup2(pipe_variables.fdout, STDOUT_FILENO);
//		close(pipe_variables.fdout);
////		signal(SIGINT, signal_handler_command);
//		if (is_buildin(common->command.simple_commands[command_table_count]))
//		{
//			execute_simple_command_buildin(common, common->command.simple_commands[command_table_count]);
//		}
//		else if (0 == (ret = fork()))							// Create child process
//		{
//			execute_simple_command(common, common->command.simple_commands[command_table_count]);
//		}
//		waitpid(ret, NULL, WUNTRACED);
//		command_table_count++;
//	}
//	restore_default_in_out_puts(&pipe_variables);
//}

int		execute_fork(t_common *common, t_simple_command *simple_command)
{}

t_pipe	pipe_variables_init(void)
{
	t_pipe				pipe_variables;

	pipe_variables.tmpin = dup(STDIN_FILENO);
	pipe_variables.tmpout = dup(STDOUT_FILENO);

	pipe_variables.fdin = pipe_variables.tmpin;
	pipe_variables.fdout = pipe_variables.tmpout;
	pipe_variables.fdpipe[0] = pipe_variables.tmpin;
	pipe_variables.fdpipe[1] = pipe_variables.tmpout;
	return (pipe_variables);
}

void	std_in_out_restore(t_pipe pipe_variables)
{
	dup2(pipe_variables.tmpin, STDIN_FILENO);
	dup2(pipe_variables.tmpout, STDOUT_FILENO);
	close(pipe_variables.tmpin);
	close(pipe_variables.tmpout);
}

void	execute_processor(t_common *common)
{
	int					ret;
	int					command_table_count;
	t_pipe				pipe_variables;
	t_simple_command	*command;

	pipe_variables = pipe_variables_init();
	command_table_count = 0;
	while (common->command.simple_commands[command_table_count])
	{
		dup2(pipe_variables.fdin, STDIN_FILENO);		//	Redirect input // подменяем stdin (fd = 0) на ранее созданный fdin
		close(pipe_variables.fdin);
		command = common->command.simple_commands[command_table_count];
		if (NULL == common->command.simple_commands[command_table_count + 1]) // если последняя комманда
			pipe_variables.fdout = simple_command_in_out_fd(command->outfile, &pipe_variables, IS_WRITE, command->is_cat);		// if fd = -1 continue;
		else
		{
			pipe(pipe_variables.fdpipe);
			pipe_variables.fdin = simple_command_in_out_fd(command->infile, &pipe_variables, IS_READ, command->is_cat);
			pipe_variables.fdout = simple_command_in_out_fd(command->outfile, &pipe_variables, IS_WRITE, command->is_cat);
		}
		dup2(pipe_variables.fdout, STDOUT_FILENO);				//	Redirect output
		close(pipe_variables.fdout);
		if (is_buildin(common->command.simple_commands[command_table_count]))
			execute_simple_command_buildin(common, common->command.simple_commands[command_table_count]);
		else if (0 == (ret = fork()))							// Create child process
			execute_simple_command(common, common->command.simple_commands[command_table_count]);
		command_table_count++;
	}
	std_in_out_restore(pipe_variables);
	waitpid(ret, NULL, WUNTRACED);
}

//		if (is_buildin(command))
//				execute_simple_command_buildin(common, command);
//			else if (0 == (ret = fork()))
//				execute_simple_command(common, command);
//			command_table_count++;
//			waitpid(ret, NULL, WUNTRACED);
//		}

void	execute_command(t_common *common, char **envp)
{
	int		command_table_len = common->command.num_of_simple_commands;	//	возможно number_of_available_simple_commands
	int		command_table_count = 0;
	int		ret;

	t_pipe	pipe_variables;

	pipe_variables.tmpin = dup(STDIN_FILENO);		//	save in
	pipe_variables.tmpout = dup(STDOUT_FILENO);		//	save out

//	if (NULL != common->command.input_file)	//	if (infile)
//		pipe_variables.fdin = open(common->command.input_file, O_RDONLY);				//	получаем ввод из файла
//	else											//	set the initial input
		pipe_variables.fdin = dup(pipe_variables.tmpin);	// use default input	//	используем стандартный ввод

	while (common->command.simple_commands[command_table_count])
	{
		//	redirect input
		dup2(pipe_variables.fdin, STDIN_FILENO);		// подменяем stdin (fd = 0) на ранее созданный fdin
		close(pipe_variables.fdin);

		//	Выбираем направление ввода и вывода
		/*		подмена стандартного ввода на fd файла с именем "file"
		**	int newfd = open("file",O_RDONLY);
		**	dup2(newfd, 0);										// теперь если писать в fd = 0 то запись будет производится в file
		**	close(newfd);
		*/
		if (command_table_count == command_table_len - 1)	//	если это последняя simple_command
		{
//			if (NULL != common->command.out_file)	//	if (outfile)
//				pipe_variables.fdout = open(common->command.out_file, O_WRONLY, O_APPEND);
//			else
				pipe_variables.fdout = dup(pipe_variables.tmpout);	//	то назначаем stdout (сохранённый ранее), результат вывода будем писать в стандартный вывод
		}
		else							//	иначе
		{
			// not last
			// simple command
			// create pipe
			pipe(pipe_variables.fdpipe);				//	создаём pipe
			pipe_variables.fdout = pipe_variables.fdpipe[1];		//	write fd назначаем на out
			pipe_variables.fdin = pipe_variables.fdpipe[0];			//	read fd назначаем на in
		}
		//	Redirect output
		dup2(pipe_variables.fdout, STDOUT_FILENO);
		close(pipe_variables.fdout);

		// Create child process
		if (0 == (ret = fork()))
		{
			execute_simple_command(common, common->command.simple_commands[command_table_count]);
//			char	**path = split_path(common->env_variables);
//			int 	count = 0;
//			char	command[100];
//
//			command[0] = '\0';
//			while (path[count])
//			{
//				ft_strlcat(command, path[count], 100);
//				ft_strlcat(command, "/", 100);
//				ft_strlcat(command, common->command.simple_commands[0]->arguments[0], 100);
//				execve(command, common->command.simple_commands[0]->arguments, envp);
//				count++;
//				command[0] = '\0';
//			}
//			errno = 0;
//			perror("execve child. Command not executed (no such command?)\n");
//			exit(0);
		}
		waitpid(ret, NULL, WUNTRACED);
		command_table_count++;
	}
	//	restore in/out defaults
	dup2(pipe_variables.tmpin, STDIN_FILENO);
	dup2(pipe_variables.tmpout, STDOUT_FILENO);
	close(pipe_variables.tmpin);
	close(pipe_variables.tmpout);
	waitpid(ret, NULL, WUNTRACED);
}

//int		main(int argc, char **argv, char **envp)
//{
//	char	***command_table = parser_temp();
//
//	ft_pipe(command_table, envp);
//	return (0);
//}

		//	Выбираем направление ввода и вывода
		//		подмена стандартного ввода на fd файла с именем "file"

//			int newfd = open("file",O_RDONLY);
//			dup2(newfd, 0);							// теперь если читать будем из fd = 0 то чтение будет из file
//			close(newfd);
