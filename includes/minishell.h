#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <sys/errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <signal.h>
# include "libft.h"

/*
** Linux has a maximum filename length of 255 characters for most filesystems (including EXT4), and a maximum path of 4096 characters.
*/

# define MAX_PATH 4096
# define MAX_NAME 255

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define BG_WHT	  "\x1B[47m" //для выделения серым
#define RESET "\x1B[0m"

/*
**	Command Data structure
*/

/*
**	Describe a simple command and arguments
*/
typedef struct			s_simple_command
{
//	int					number_of_available_arguments;	//	Available space for arguments currently preallocated
	int 				current_arg;			//	Number of argument
	char				**arguments;					//	fixme Array of arguments
	int 				arg_count; // количество аргументов = number_of_available_arguments
	int 				have_pipe;

	int 				num_of_outfiles;
	char				**out_file;		// путь к файлу для записи в него результата (редирект ">")
	int 				current_outfile;
	char				**out_file_cat;		// путь к файлу для записи в него результата (редирект ">>")


//	int 				memory_allocated;
//	int					i; // counter
//	int					flag;	//space flag;
//	int 				k; // number of argument
//	int 				j; //счетчик символов по строке аргумента
//	int					quotes;

	//	SimpleCommand();								// функция для создания simple_command
	//	void insertArgument(char *argument);			// функция для вставки аргумента в simple_command
}						t_simple_command;

/*
**	Describe a complete command with the multiple pipes if any
**	and input/output redirection if any.
*/

typedef struct			s_command
{
	int					current_simple_command; // текущая симпл команда( для движения по массиву **simple_commands)
	int 				num_of_simple_commands;  // количество симпл команд

	t_simple_command	**simple_commands;	//fixme

	char				**out_file;		// путь к файлу для записи в него результата (редирект ">")
	char				*out_file_cat;		// путь к файлу для записи в него результата (редирект ">")
	char 				*input_file; // путь к файлу для чтения из него ввода (редирект "<")
	char 				*err_file;		// путь к файлу для записи в него вывода ошибки (редирект >&)
	int 				background;// ?
}						t_command;

typedef struct			s_common
{
	t_command			command;
	char 				**env_variables;		// не нужно удалять используется в функции execve() для исполнения команд
	char 				***env_variables_list;
}						t_common;

/*
** parser
*/

int					get_next_line(int fd, char **line);
int					ft_parser(t_common *common, char *line);
int					pars(t_common *common, char *line);
int					new_pars(t_common *common, char *line);
size_t				ft_strlen_to_char(const char *s, char c);
int					make_arg(char *f_line , t_simple_command *sc);
int 				make_args(char *line, t_common *common, int increment);
void				ft_init_current_command(t_common *common, char *line);
int					ft_arg_counter(char *s);
int 				do_all_spec(t_common *common, char *line, char curent_char, int increment);
int					ft_redirect_counter(char *line, char redirect_char);
int					do_redirect(t_common *common, char *line);
void				do_pipe(t_common *common, char *line);
int					ft_simple_command_counter(char *line);
void				ft_init_simple_commands(t_common *common, char *line, int current_command);
void				ft_init_outfiles(t_common *common, char *line, int current_command);

/*
** executor
*/

void				pre_executor(int argc, char **argv, char **envp);
void 				executor(t_common *common);
void				execute_command(t_common *common, char **envp);

void				execute_simple_command_buildin(t_common *common, t_simple_command *simple_command);
void				execute_simple_command(t_common *common, t_simple_command *simple_command);
int					is_buildin(t_simple_command *simple_command);

/*
 * pre_executor
 */

void				fork_execution(char **command, char **envp);

char				***parser_temp(void);
void				ft_pipe(char ***command_table, char **envp);

/*
** utils
*/

char				**copy_envp(char **envp);
size_t				list_len(const char **list);
void				ft_putenv(char **envp);
void				ft_putenv_arg(char *line);

char				**split_path(char **envp);
void				ft_free_list(char ***split_list);

void				free_line_list(char **split_list);

t_common			common_init(char **envp);
t_command			command_init(void);
t_simple_command	*simple_command_init(
								char **arguments,
								int number_of_arguments,
								int number_of_available_arguments
);

char				*get_envp_variable(t_common *common, char *var);
char				*get_envp_line(t_common *common, char *line);
char				***get_envp(char **envp);
int					update_envp_var(t_common *common, char *key, char *new_value, int append);
int					get_envp_var_index(t_common *common, char *var);
char				*get_envp_var_pointer(t_common *common, char *var);
void				free_arg_list(char ****arg_list);
char				**get_key_value(char *envp_line);

/*
** buildins
*/

void				mini_cd(char **simple_command, t_common *common);
void				mini_echo(char **simple_command);
void				mini_pwd(t_common *common);
void				mini_export(t_common *common, char **simple_command);
void				mini_env(t_common *common);
void				mini_unset(t_common *common, char **keys);
void				mini_exit(t_common *common);
char				*get_pwd(char **envp);

/*
** signals
*/

void				signal_processor(void);
void				signal_handler(int num);
void				signal_handler_command(int num);

#endif