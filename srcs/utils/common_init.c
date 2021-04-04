#include "minishell.h"

/*
**	создание пустой структуры t_simple_command
*/

//t_simple_command	*one_simple_command_init(
//		char **arguments,
//		int number_of_arguments,
//		int number_of_available_arguments
//		)
//{
//	t_simple_command	*simple_command;
//
//	simple_command = NULL;
//	if (NULL == (simple_command = malloc(sizeof(t_simple_command))))
//		return (NULL);
//	simple_command->arguments = arguments;
//	simple_command->current_arg = number_of_arguments;
////	simple_command->arg_count = number_of_available_arguments;
//	return (simple_command);
//}

/*
**	создание пустой структуры t_command
*/

void		command_init(t_common *common)
{
//	common->command.num_of_simple_commands = 0;

	common->command.simple_commands = NULL;

	common->command.out_file = NULL;
	common->command.infile = NULL;
	common->command.err_file = NULL;

	common->command.background = 0;
	common->command.current_simple_command = 0;
}

/*
**	создание пустой структуры t_common
*/

t_common	*common_init(char **envp)
{
	t_common	*common;

	common = malloc(sizeof(t_common));
	common->env_variables_list = get_envp(envp);		//	разбивает envp на название переменной и значение переменной
	common->env_variables = envp;			//	просто копирует envp
	command_init(common);
	common->termcap = t_termcap_init();
	return (common);
}
