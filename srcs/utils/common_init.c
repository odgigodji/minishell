#include "minishell.h"

/*
typedef struct			s_command
{
	int					number_of_available_simple_commands;
	int 				number_of_simple_commands;

	char				***simple_commands;
	t_simple_command	*simple_commands_struct;

	char				*out_file;		// путь к файлу для записи в него результата (редирект ">")
	char 				*input_file;	// путь к файлу для чтения из него ввода (редирект "<")
	char 				*err_file;		// путь к файлу для записи в него вывода ошибки (редирект >&)
	int 				background;		// ?
}						t_command;
*/

t_command	command_init(void)
{
	t_command	command;

	command.number_of_available_simple_commands = 0;
	command.number_of_simple_commands = 0;

	command.simple_commands_struct = NULL;
	command.simple_commands = NULL;

	command.out_file = NULL;
	command.input_file = NULL;
	command.err_file = NULL;

	command.background = 0;
	return (command);
}

t_common	common_init(char **envp)
{
	t_common common;

	common.env_variables = copy_envp(envp);
	common.command = command_init();
	return (common);
}
