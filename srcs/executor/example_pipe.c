#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "../../libft/libft.h"

int	main(int argc, char **argv, char **envp)
{
	char*	command_ls[]={"/bin/ls", "-l", NULL};
	char*	command_cat[]={"/bin/cat", "-e", NULL};
	char*	command_grep[]={"/usr/bin/grep", "pipe", NULL};
	char	**command_table[5];
	command_table[0] = command_ls;
	command_table[1] = command_cat;
	command_table[2] = command_grep;
	command_table[3] = NULL;

	//	save in/out
	int 	tmpin = dup(0);
	int		tmpout = dup(1);

	//	set the initial input
	int		fdin;
	int		infile = 0;
	fdin = dup(tmpin); // use default input

	int		ret;
	int		fdout;
	int		command_table_count = 0;

	while (command_table[command_table_count])
	{
		// redirect input
		dup2(fdin, 0);
		close(fdin);

		if (command_table_count == 2)
		{
			// use default output
			fdout = dup(tmpout);
		}
		else
		{
			// simple command
			// create pipe
			int fdpipe[2];
			pipe(fdpipe);
			fdout = fdpipe[1];
			fdin = fdpipe[0];
		}
		// Redirect output
		dup2(fdout, 1);
		close(fdout);

		// Create child process
		ret = fork();
		if (ret == 0)
		{
			execve(command_table[command_table_count][0], command_table[command_table_count], envp);
			perror(command_table[command_table_count][0]);
			perror("execve child\n");
			exit(0);
		}
		command_table_count++;
	}
	//	restore in/out defaults
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	waitpid(ret, NULL, WUNTRACED);

	return (0);
}
