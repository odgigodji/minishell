#include "minishell.h"

/*
typedef struct			s_simple_command
{
	int					number_of_available_arguments;	//	Available space for arguments currently preallocated
	int 				number_of_arguments;			//	Number of arguments
	char				**arguments;					//	fixme Array of arguments

	//	SimpleCommand();								// функция для создания simple_command
	//	void insertArgument(char *argument);			// функция для вставки аргумента в simple_command
}						t_simple_command;

typedef struct			s_command
{
	int					number_of_available_simple_commands;
	int 				number_of_simple_commands;

	char				***simple_commands;
	t_simple_command	**simple_commands_struct;	//fixme

	char				*out_file;		// путь к файлу для записи в него результата (редирект ">")
	char 				*input_file;	// путь к файлу для чтения из него ввода (редирект "<")
	char 				*err_file;		// путь к файлу для записи в него вывода ошибки (редирект >&)
	int 				background;		// ?
}						t_command;
*/

void	executor(t_common *common)
{
//	fork_execution(
//			common.command.simple_commands_struct[0]->arguments,
//			common.env_variables
//			);
	execute_command(common, common->env_variables);
}