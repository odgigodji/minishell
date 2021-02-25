#include "minishell.h"

char	***parser_temp(void)
{
	char				***command_table = malloc(sizeof(char **) * 5);
	int					command_len = 50;
	t_command			command;
	t_simple_command	*simple_command;

	char	**command_ls = malloc(sizeof(char *) * 10);
	command_ls[0] = malloc(sizeof(char) * command_len);
	ft_strlcpy(command_ls[0], "/bin/ls", command_len);
	command_ls[1] = malloc(sizeof(char) * command_len);
	ft_strlcpy(command_ls[1], "-l", command_len);
	command_ls[2] = NULL;

	char	**command_cat = malloc(sizeof(char *) * 10);
	command_cat[0] = malloc(sizeof(char) * command_len);
	ft_strlcpy(command_cat[0], "/bin/cat", command_len);
	command_cat[1] = malloc(sizeof(char) * command_len);
	ft_strlcpy(command_cat[1], "-e", command_len);
	command_cat[2] = NULL;

	char	**command_grep = malloc(sizeof(char *) * 10);
	command_grep[0] = malloc(sizeof(char) * command_len);
	ft_strlcpy(command_grep[0], "/usr/bin/grep", command_len);
	command_grep[1] = malloc(sizeof(char) * command_len);
	ft_strlcpy(command_grep[1], "Make", command_len);
	command_grep[2] = NULL;

	command_table[0] = command_ls;
	command_table[1] = command_cat;
	command_table[2] = command_grep;
	command_table[3] = NULL;

	return (command_table);
}

size_t	ft_command_table_len(char ***command_table)
{
	size_t	count;

	count = 0;
	while (command_table[count])
		count++;
	return (count);
}

void	execute_command(t_common common, char **envp)
{
	int		command_table_len = common.command.number_of_simple_commands;	//	возможно number_of_available_simple_commands

	int 	tmpin = dup(STDIN_FILENO);		//	save in
	int		tmpout = dup(STDOUT_FILENO);	//	save out

	int		fdin;
	int		infile = 0;		// на время пока не сделаны редиректы
	int		outfile = 0;	// на время пока не сделаны редиректы

	if (common.command.input_file)	//	if (infile)
		fdin = open(common.command.input_file, O_RDONLY);				//	получаем ввод из файла
	else											//	set the initial input
		fdin = dup(tmpin);	// use default input	//	используем стандартный ввод

	int		ret;
	int		fdout;
	int		command_table_count = 0;
	int 	fdpipe[2];

	while (common.command.simple_commands_struct[0]->arguments[command_table_count])
	{
		//	redirect input
		dup2(fdin, STDIN_FILENO);		// подменяем stdin (fd = 0) на ранее созданный fdin
		close(fdin);

		//	Выбираем направление ввода и вывода
		/*		подмена стандартного ввода на fd файла с именем "file"
		**	int newfd=open("file",O_RDONLY);
		**	dup2(newfd, 0);										// теперь если писать в fd = 0 то запись будет производится в file
		**	close(newfd);
		*/
		if (command_table_count == command_table_len - 1)	//	если это последняя simple_command
		{
			if (common.command.out_file)	//	if (outfile)
				fdout = open(common.command.out_file, O_WRONLY, O_APPEND);
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
			char	**path = split_path(common.env_variables);
			int 	count = 0;
			char	command[100];

			while (path[count])
			{
				ft_strlcat(command, path[count], 100);
				ft_strlcat(command, "/", 100);
				ft_strlcat(command, common.command.simple_commands_struct[0]->arguments[0], 100);
				execve(common.command.simple_commands_struct[0]->arguments[0], common.command.simple_commands_struct[0]->arguments, envp);
				count++;
			}
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



void	ft_pipe(char ***command_table, char **envp)
{
	int		command_table_len = ft_command_table_len(command_table);

	int 	tmpin = dup(STDIN_FILENO);		//	save in
	int		tmpout = dup(STDOUT_FILENO);	//	save out

	int		fdin;
	int		infile = 0;
	int		outfile = 0;
	if (infile)
		fdin = open(infile, O_RDONLY);				//	получаем ввод из файла
	else											//	set the initial input
		fdin = dup(tmpin);	// use default input	//	используем стандартный ввод

	int		ret;
	int		fdout;
	int		command_table_count = 0;
	int 	fdpipe[2];

	while (command_table[command_table_count])
	{
		//	redirect input
		dup2(fdin, STDIN_FILENO);		// подменяем stdin (fd = 0) на ранее созданный fdin
		close(fdin);

		//	Выбираем направление ввода и вывода
		/*		подмена стандартного ввода на fd файла с именем "file"
		**	int newfd=open("file",O_RDONLY);
		**	dup2(newfd, 0);										// теперь если писать в fd = 0 то запись будет производится в file
		**	close(newfd);
		*/
		if (command_table_count == command_table_len - 1)	//	если это последняя simple_command
		{
			if (outfile)
				fdout = open(outfile, O_WRONLY, O_APPEND);
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
			execve(command_table[command_table_count][0], command_table[command_table_count], envp);
			printf("|%s|\n", command_table[command_table_count][0]);
			perror("execve child. Command not executed\n");
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
