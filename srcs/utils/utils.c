#include "minishell.h"

char **init_args(char **lexer_result, char *spec_token)
{
	char **arguments;

	arguments = ft_calloc((num_of_args(lexer_result, spec_token) + 1), sizeof(char *));
//	arguments[num_of_args(lexer_result, spec_token)] = NULL;
//	if (!ft_strcmp(spec_token, GREAT))
//		printf(RED"GREAT COUNT_ARG %d\n"RESET, num_of_args(lexer_result, GREAT));
//	else
//		printf(RED"COUNT_ARG %d\n"RESET, num_of_args(lexer_result, PIPE));
	return (arguments);
}

int num_of_args(char **lexer_result, char *spec_token)
{
	int num_of_arg;

	num_of_arg = 0;
	while(lexer_result[num_of_arg] && ft_strcmp(PIPE, lexer_result[num_of_arg]) &&\
	ft_strcmp(spec_token, lexer_result[num_of_arg]))
		num_of_arg++;
	return (num_of_arg);
}

int num_of_simple_commands(char **lexer_result)
{
	int count_of_simple_command;

	count_of_simple_command = 1;  //min 1 command
	while(lexer_result && *lexer_result)
	{
		if (!ft_strcmp(PIPE, *lexer_result))
			count_of_simple_command++;
		lexer_result++;
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

t_simple_command	*one_simple_command_init(char **lexer_result)
{
	t_simple_command	*simple_command;

	simple_command = NULL;
	simple_command = malloc(sizeof(t_simple_command *));
	return (simple_command);
}