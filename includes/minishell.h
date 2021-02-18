#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include "libft.h"

/*
**	Command Data structure
*/

/*
**	Describe a simple command and arguments
*/

typedef struct	s_simple_command
{
	//	Available space for arguments currently preallocated
	int		number_of_available_arguments;
	//	Number of arguments
	int		number_of_arguments;
	//	Array of arguments
	char	**arguments;
}				t_simple_command;


/*
**	Describe a complete command with the multiple pipes if any
**	and input/output redirection if any.
*/

typedef struct	s_command
{
	int					number_of_available_simple_commands;
	int 				number_of_simple_commands;
	t_simple_command	**simple_commands;
	char				*out_file;
	char 				*input_file;
	char 				*err_file;
	int 				background;


}				t_command;


int		get_next_line(int fd, char **line);

void	pre_executer(int argc, char **argv, char **envp);

#endif