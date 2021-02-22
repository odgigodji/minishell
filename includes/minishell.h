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

char			**arguments;

/*
**	Describe a complete command with the multiple pipes if any
**	and input/output redirection if any.
*/

typedef struct	s_command
{
	int			number_of_available_simple_commands;
	int 		number_of_simple_commands;
	char		***simple_commands;
	char		*out_file;
	char 		*input_file;
	char 		*err_file;
	int 		background;
}				t_command;


int				get_next_line(int fd, char **line);
void			pre_executer(int argc, char **argv, char **envp);
int				ft_parser(void);
int				ft_lexer(char *line);
#endif