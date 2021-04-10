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

# include <term.h>
# include <termios.h>

/*
** Linux has a maximum filename length of 255 characters for most filesystems (including EXT4), and a maximum path of 4096 characters.
*/

# define MAX_PATH 4096
# define MAX_NAME 255

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m" //violet
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define BG_WHT	  "\x1B[47m" //для выделения серым
#define RESET "\x1B[0m"

# define SHELL_NAME "minishell"

# define IS_READ 1
# define IS_WRITE 0
# define IS_CAT 1
# define IS_NOT_CAT 0

# define SPEC_SYMBOL "|<>;"
//# define SPEC_SYMBOL " '|\"$\t<>"
# define GREAT "<GREAT>"				// ">"
# define GREATGREAT "<GREATGREAT>"		// ">>"
# define LESS "<LESS>"					// "<"
# define GREATLESS "<GREATLESS>"		// "<<"
# define PIPE "<PIPE>"					// "|"
# define VAR "<VAR>"					// "$"
# define ACTUAL_POSITION_IN_LEXER_RESULT lexer_result + *current_token
# define NOT_LAST_TOKEN current_token < last_token //?=
# define ACTUAL_TOKEN lexer_result[*current_token]

/*
**	Command Data structure
*/

/*
**	Describe a simple command and arguments
*/

typedef struct			s_simple_command
{
	char				**arguments;					//	fixme Array of arguments
	char				**outfiles;		// путь к файлу для записи в него результата (редирект ">")
	char				**infiles;		// путь к файлу для записи в него результата (редирект ">")
	int					is_cat;
}						t_simple_command;

/*
**	Describe a complete command with the multiple pipes if any
**	and input/output redirection if any.
*/

typedef struct			s_command
{
	t_simple_command	**simple_commands;	//fixme
}						t_command;

typedef struct	s_termcap
{
	struct termios		term;
	char				*term_name;
//	char				*temp;

	char				**history;
	int					history_count;
	int					history_cursor;
	int					history_len;

	int					cursor;
//	struct winsize		win;
}				t_termcap;

typedef struct			s_common
{
	t_command			command;
	char 				**env_variables;		// не нужно удалять используется в функции execve() для исполнения команд
	char 				***env_variables_list;
	t_termcap			*termcap;
}						t_common;

typedef struct			s_pipe
{
	int tmpin;
	int tmpout;

	int	fdin;
	int	fdout;

	int fdpipe[2];
}						t_pipe;

int	g_signal_process_status;

/*
**	Временные функции
*/

void				ft_printf_outfile_info(t_common *common);

void				ft_print_lexer_result(char **lexer_result);
void 				ft_print_args(char **arguments);
void 				ft_print_simple_comand(t_simple_command *simple_command);
void				ft_print_all_command(t_simple_command **command_table);

//int		ft_array_len(char	**arg_list); // fixme удалить

/*
** is_valid
*/

int					invalid_lexer_result(char **lexer_result);
int					syntax_error(const char *line);
int					next_symbol_after_space(const char *line);
//int					ft_empty_line(const char *line);
int 				with_error(const int unexpected_token);
/*
** parser
*/

int					get_next_line(int fd, char **line);
size_t				ft_strlen_to_char(const char *s, char c);
int is_redirect(char *actual_token);

t_command get_command_table(char **lexer_result);
t_simple_command *get_simple_command(char **lexer_result, int *current_token);
t_simple_command	*one_simple_command_init(char **lexer_result);
t_simple_command	**command_table_init(char **lexer_result);
char **init_args(char **lexer_result, char *spec_token);


char				**lexer(char *line, t_common *common);
char				toggle_brace_flag_lexer(char flag, char current_char);
int					toggle_back_slash_flag(int flag, char *line, int count);
int					expand_variable(char *token, t_common *common, char **result, int *count_result);
int					get_token3(char *line, char **token, t_common *common);
/*
** counters
*/
int 				num_of_simple_commands(char **lexer_result);
int 				num_of_args(char **lexer_result, char *spec_token);


/*
** executor
*/

void				pre_executor(int argc, char **argv, char **envp);
void 				executor(t_common *common);
void				execute_command(t_common *common, char **envp);

void				execute_simple_command_buildin(t_common *common, t_simple_command *simple_command);
void				execute_simple_command(t_common *common, t_simple_command *simple_command);
int					is_buildin(t_simple_command *simple_command);
void				execute_processor(t_common *common, t_pipe *pipe_variables);
void				execute_preprocessing(t_common *common);

/*
 * pre_executor
 */

void				fork_execution(char **command, char **envp);

char				***parser_temp(void);
void				ft_pipe(char ***command_table, char **envp);

/*
** utils
*/

void				prompt(void);
char				**copy_envp(char **envp);
size_t				list_len(const char **list);
void				ft_putenv(char **envp);
void				ft_putenv_arg(char *line);

char				**split_path(t_common *common);
void				ft_free_list(char ***split_list);

void				free_line_list(char **split_list);

t_common			*common_init(char **envp);
void				command_init(t_common *common);


char				*get_envp_variable(t_common *common, char *var);
char				*get_envp_line(t_common *common, char *line);
char				***get_envp(char **envp);
int					update_envp_var(t_common *common, char *key, char *new_value, int append);
int					get_envp_var_index(t_common *common, char *var);
char				*get_envp_var_pointer(t_common *common, char *var);
void				free_arg_list(char ****arg_list);
char				**get_key_and_value(char *envp_line);
int					args_list_len(char	***arg_list);
char				**make_envp(t_common *common);

int					simple_command_open_file(char *file, int is_read, int is_cat);
int					simple_command_in_out_fd(char **files_list, t_pipe *pipe_variables, int is_read, int is_cat);

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

/*
** termcap
*/
int					t_get_next_line(char **line, t_termcap *termcap);
void				to_cannon(void);
void				t_term_to_cannon(t_termcap *termcap);
t_termcap			*t_termcap_init(void);
int					ft_putchar_term(int c);

#endif