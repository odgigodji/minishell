#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "libft.h"

char	***parser_temp(void)
{
	char	***command_table = malloc(sizeof(char **) * 5);
	int		command_len = 50;

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

void	ft_pipe(char ***command_table, char **envp)
{
	int		command_table_len = ft_command_table_len(command_table);
	//	save in/out
	int 	tmpin = dup(STDIN_FILENO);
	int		tmpout = dup(STDOUT_FILENO);

	//	set the initial input
	int		fdin;
	int		infile = 0;
	fdin = dup(tmpin); // use default input

	int		ret;
	int		fdout;
	int		command_table_count = 0;
	int 	fdpipe[2];

	while (command_table[command_table_count])
	{
		// redirect input
		dup2(fdin, STDIN_FILENO);
		close(fdin);

		if (command_table_count == command_table_len - 1)
		{
			// use default output
			fdout = dup(tmpout);
		}
		else
		{
			// simple command
			// create pipe
			pipe(fdpipe);
			fdout = fdpipe[1];
			fdin = fdpipe[0];
		}
		// Redirect output
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

int		main(int argc, char **argv, char **envp)
{
	char	***command_table = parser_temp();

	ft_pipe(command_table, envp);
	return (0);
}
