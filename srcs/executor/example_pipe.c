#include "minishell.h"

void	execute_command(t_common *common, char **envp)
{
	int		command_table_len = common->command.number_of_simple_commands;	//	возможно number_of_available_simple_commands

	int 	tmpin;
	int		tmpout;
	tmpin = dup(STDIN_FILENO);		//	save in
	tmpout = dup(STDOUT_FILENO);	//	save out

	int		fdin;

	if (NULL != common->command.input_file)	//	if (infile)
		fdin = open(common->command.input_file, O_RDONLY);				//	получаем ввод из файла
	else											//	set the initial input
		fdin = dup(tmpin);	// use default input	//	используем стандартный ввод

	int		ret;
	int		fdout;
	int		command_table_count = 0;
	int 	fdpipe[2];

	while (common->command.simple_commands[0]->arguments[command_table_count])
	{
		//	redirect input
		dup2(fdin, STDIN_FILENO);		// подменяем stdin (fd = 0) на ранее созданный fdin
		close(fdin);

		//	Выбираем направление ввода и вывода
		/*		подмена стандартного ввода на fd файла с именем "file"
		**	int newfd = open("file",O_RDONLY);
		**	dup2(newfd, 0);										// теперь если писать в fd = 0 то запись будет производится в file
		**	close(newfd);
		*/
		if (command_table_count == command_table_len - 1)	//	если это последняя simple_command
		{
			if (NULL != common->command.out_file)	//	if (outfile)
				fdout = open(common->command.out_file, O_WRONLY, O_APPEND);
			else
				fdout = dup(tmpout);	//	то назначаем stdout (сохранённый ранее), результат вывода будем писать в стандартный вывод
		}
		else							//	иначе
		{
			// not last
			// simple command
			// create pipe
			pipe(fdpipe);				//	создаём pipe
			fdout = fdpipe[1];			//	write fd назначаем на out
			fdin = fdpipe[0];			//	read fd назначаем на in
		}
		//	Redirect output
		dup2(fdout, STDOUT_FILENO);
		close(fdout);

		// Create child process
		ret = fork();
		if (ret == 0)
		{
			char	**path = split_path(common->env_variables);
			int 	count = 0;
			char	command[100];

			command[0] = '\0';
			while (path[count])
			{
				ft_strlcat(command, path[count], 100);
				ft_strlcat(command, "/", 100);
				ft_strlcat(command, common->command.simple_commands[0]->arguments[0], 100);
				execve(command, common->command.simple_commands[0]->arguments, envp);
				count++;
				command[0] = '\0';
			}
			errno = 0;
			perror("execve child. Command not executed (no such command?)\n");
			exit(0);
		}
		command_table_count++;
	}
	//	restore in/out defaults
	dup2(tmpin, STDIN_FILENO);
	dup2(tmpout, STDOUT_FILENO);
	close(tmpin);
	close(tmpout);
	waitpid(ret, NULL, WUNTRACED);
}

//int		main(int argc, char **argv, char **envp)
//{
//	char	***command_table = parser_temp();
//
//	ft_pipe(command_table, envp);
//	return (0);
//}
