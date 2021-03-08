#include "minishell.h"

/*
typedef struct			s_command
{
	int					number_of_available_simple_commands;
	int 				number_of_simple_commands;

	char				***simple_commands;
	t_simple_command	**simple_commands_struct;

	char				*out_file;		// путь к файлу для записи в него результата (редирект ">")
	char 				*input_file;	// путь к файлу для чтения из него ввода (редирект "<")
	char 				*err_file;		// путь к файлу для записи в него вывода ошибки (редирект >&)
	int 				background;		// ?
}						t_command;
*/

/*
**	создание пустой структуры t_simple_command
*/

t_simple_command	*simple_command_init(
		char **arguments,
		int number_of_arguments,
		int number_of_available_arguments
		)
{
	t_simple_command	*simple_command;

	simple_command = NULL;
	if (NULL == (simple_command = malloc(sizeof(t_simple_command))))
		return (NULL);
	simple_command->arguments = arguments;
	simple_command->number_of_arguments = number_of_arguments;
	simple_command->number_of_available_arguments = number_of_available_arguments;
	return (simple_command);
}

/*
**	создание пустой структуры t_command
*/

t_command	command_init(void)
{
	t_command	command;

	command.number_of_available_simple_commands = 0;
	command.number_of_simple_commands = 0;

	command.simple_commands = NULL;
	command.simple_commands = NULL;

	command.out_file = NULL;
	command.input_file = NULL;
	command.err_file = NULL;

	command.background = 0;
	return (command);
}

/*
**	создание пустой структуры t_common
*/

t_common	common_init(char **envp)
{
	t_common common;

	common.env_variables = copy_envp(envp);
	common.command = command_init();
	return (common);
}
