#include "minishell.h"

char **init_args(char **lexer_result)
{
	char **args;

	args = ft_calloc((num_of_args(lexer_result) + 1), sizeof(char *));
	args[num_of_args(lexer_result)] = NULL;
	return (args);
}

int num_of_args(char **lexer_result)
{
	int num_of_arg;

	num_of_arg = 0;
	while(lexer_result[num_of_arg] && ft_strncmp(PIPE, lexer_result[num_of_arg], ft_strlen(PIPE)))
		num_of_arg++;
	printf(RED"COUNT_ARG %d\n"RESET, num_of_arg);
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