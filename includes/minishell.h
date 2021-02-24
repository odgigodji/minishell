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
	int		number_of_available_arguments;	//	Available space for arguments currently preallocated

	int 	number_of_arguments;			//	Number of arguments

	char	**arguments;					//	fixme Array of arguments

	//	SimpleCommand();
	//	void insertArgument( char * argument );
}				t_simple_command;

/*
**	Describe a complete command with the multiple pipes if any
**	and input/output redirection if any.
*/

typedef struct	s_command
{
	int			number_of_available_simple_commands;
	int 		number_of_simple_commands;

	char		***simple_commands;
	t_simple_command		*simple_commands_struct;	//fixme

	char		*out_file;
	char 		*input_file;
	char 		*err_file;
	int 		background;
}				t_command;

typedef struct	s_common
{
	t_command	command;
	char 		**env_variables;
}				t_common;

int				get_next_line(int fd, char **line);
int				ft_parser(t_common *common);
int				ft_lexer(char *line);

/*
** executor
*/

void			pre_executor(int argc, char **argv, char **envp);
void 			executor(t_common common);

/*
 * pre_executor
 */

void			fork_execution(char **command, char **envp);

/*
** utils
*/

char			**copy_envp(char const **envp);
size_t			list_len(const char **list);
void			ft_putenv(char **envp);
void			ft_putenv_arg(char *line);

#endif