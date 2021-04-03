#include "minishell.h"

char **init_args(char **lexer_result)
{
	char **args;

	args = ft_calloc((num_of_args(lexer_result) + 1), sizeof(char *));
	args[num_of_args(lexer_result)] = NULL;
	printf(RED"COUNT_ARG %d\n"RESET, num_of_args(lexer_result));
	return (args);
}

int num_of_args(char **lexer_result)
{
	int num_of_arg;

	num_of_arg = 0;
	while(lexer_result[num_of_arg] && ft_strncmp(PIPE, lexer_result[num_of_arg], ft_strlen(PIPE)))
		num_of_arg++;
	return (num_of_arg);
}

int num_of_simple_commands(char **lexer_result)
{
	int counter;
	int count_of_simple_command;

	counter = 0;
	count_of_simple_command = 1;  //min 1 command
	while(lexer_result && lexer_result[counter])
	{
		if (TOKEN_IS_PIPE)
			count_of_simple_command++;
		counter++;
	}
	return (count_of_simple_command);
}

/*
** выделение памяти на simple_commands (simple_commands)
*/

t_simple_command	**command_table_init(char **lexer_result)
{
	t_simple_command	**command_table; // называется simple_commands в нашей структуре

	command_table = NULL; // выделить память и занулить переменные
	command_table = ft_calloc(num_of_simple_commands(lexer_result) + 1, sizeof(char *));
	command_table[num_of_simple_commands(lexer_result)] = NULL;
	printf(RED"COUNT_SC %d\n"RESET, num_of_simple_commands(lexer_result));
	return (command_table);
}

/*
** выделение памяти на одну simple_command (например на ["ls", "-l"])
*/

t_simple_command	*simple_command_init(char **lexer_result)
{
	t_simple_command	*simple_command;

	simple_command = NULL;
	simple_command = malloc(sizeof(t_simple_command *));
	simple_command->arguments = init_args(lexer_result);
	return (simple_command);
}