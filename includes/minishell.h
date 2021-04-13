#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
//# include <sys/errno.h>
# include <errno.h>
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

//# define MAX_PATH 4096
# define MAX_PATH 4000
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
	char				*line;

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

typedef struct	s_token_flag
{
	char	brace_single;
	char	brace_double;
	char	back_slash;
}				t_token_flag;

int	g_errno;

/*
**	Временные функции
*/

void				ft_printf_outfile_info(t_common *common);

void				ft_print_lexer_result(char **lexer_result);
void 				ft_print_args(char **arguments);
void 				ft_print_simple_comand(t_simple_command *simple_command);
void				ft_print_all_command(t_simple_command **command_table);
int					ft_empty_line(const char *line);
int		ft_array_len(char	**arg_list); // fixme удалить

/*
** is_valid
*/

int					invalid_lexer_result(char **lexer_result);
int					syntax_error(const char *line);
int					next_after_space(const char *line);
//int					ft_empty_line(const char *line);
int 				with_error(const int unexpected_token);
int next_char_is_shielded(const char *line, int *i);
int	we_are_in_quotes(const char *line, int i);
char	check_line_2(const char *line, int i, int quotes_flag, char quote_type);

/*
**	Termcap
*/

int			t_history_memory_processing(t_termcap *termcap);
int			t_history_memory_pr_realloc(t_termcap *termcap);
void		t_history_memory_pr_no_realloc(t_termcap *termcap, int history_len);
int			get_history_len(char **history);

void		to_icannon(void);
void		to_cannon(void);
t_termcap	*t_termcap_init(void);
int			ft_putchar_term(int c);

int			t_key_handle(char *buffer, t_termcap *termcap, char **line);
void		t_key_handle_down(char *buffer, t_termcap *termcap, char **line);
void		t_key_handle_up(char *buffer, t_termcap *termcap, char **line);
int			is_key(char *line);

int			t_termcap_input_handle(char *buffer, t_termcap *termcap,
							 char **line, int read_rv);
int			t_termcap_pre(t_termcap *termcap);
int			t_input_handle(char *buffer, t_termcap *termcap, char **line,
					int read_rv);
int			t_handle_signal(char *buffer, t_termcap *termcap);
int			t_is_signal(char *buffer, t_termcap *termcap);


/*
** parser
*/

void ft_kitty(char *line_is_kitty);
int					get_next_line(int fd, char **line);
size_t				ft_strlen_to_char(const char *s, char c);
int is_redirect(char *actual_token);

t_command get_command_table(char **lexer_result);
t_simple_command *get_simple_command(char **lexer_result, int *current_token);
t_simple_command	*one_simple_command_init(char **lexer_result);
t_simple_command	**command_table_init(char **lexer_result);
char **init_args(char **lexer_result, char *spec_token);
char **get_outfiles(char **lexer_result, int *is_cat);
char **get_infiles(char **lexer_result);
void pass_redirect_files(char **lexer_result, int *current_token);



/*
** counters
*/
int 				num_of_simple_commands(char **lexer_result);
int 				num_of_args(char **lexer_result, char *spec_token);

/*
**	Lexer
*/

char				**lexer(char *line, t_common *common);
char				toggle_brace_flag_lexer(char flag, char current_char);
int					toggle_back_slash_flag(int flag, char *line, int count);
int					expand_variable(char *token, t_common *common, char **result, int *count_result);
int					get_token3(char *line, char **token, t_common *common);
int					get_spec_token(char *line, char **token);
int					is_spec_symbol(char c);

void	get_token_char(char **buffer_token, char *line, int *count_token, int *count_line);
int		get_token_ret(t_token_flag *f, char **buffer_token, int count_token, char **token);
int		get_token_is_var(t_token_flag *f, char *line, int count_line);
int		get_token_is_end(t_token_flag *f, char *line, int count_line);
int		get_token_toggle_flag(t_token_flag *f, char *line, int *count_line);
void	get_token_flag_init(t_token_flag *f, int *count_line, int *count_token);

/*
**	Executor
*/

void				pre_executor(int argc, char **argv, char **envp);
void 				executor(t_common *common);
void				execute_command(t_common *common, char **envp);

void				execute_simple_command_buildin(t_common *common, t_simple_command *simple_command);
void				execute_simple_command(t_common *common, t_simple_command *simple_command, t_pipe *pipe_variables);
int					is_buildin(t_simple_command *simple_command);
void				execute_processor(t_common *common, t_pipe *pipe_variables);
void				execute_preprocessing(t_common *common);
void				close_fd(t_pipe *pipe_variables);

/*
**	Pre_executor
*/

void				fork_execution(char **command, char **envp);

char				***parser_temp(void);
void				ft_pipe(char ***command_table, char **envp);

/*
**	Utils
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
void	free_lexer_results(char ***lexer_results);
void	free_command_table(t_common *common);
char	*shift_line(char *line);
/*
**	Buildins
*/

void				mini_cd(char **simple_command, t_common *common);
void				mini_echo(char **simple_command);
void				mini_pwd(void);
void				mini_export(t_common *common, char **simple_command);
void				mini_env(t_common *common);
void				mini_unset(t_common *common, char **keys);
void				mini_exit(t_common *common);
void				mini_hello(void);

int					is_key_valid(char *key);
int					not_valid_key_return(char *key, int count);

/*
**	Signals
*/

void				signal_processor(void);
void				signal_handler(int num);
void				signal_handler_command(int num);

/*
**	Termcap
*/

int					t_get_next_line(char **line, t_termcap *termcap);
void				to_cannon(void);
void				t_term_to_cannon(t_termcap *termcap);
t_termcap			*t_termcap_init(void);
int					ft_putchar_term(int c);

/*
**	Free
*/

void				free_argument_list(char ***list);

#endif