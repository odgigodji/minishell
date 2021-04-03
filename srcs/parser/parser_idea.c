#include <tcl.h>
#include "minishell.h"

char **get_outfiles(char **lexer_result, int *current_token)
{

	return(0);
}

char **get_args(char **lexer_result, int *current_token)
{
//	printf(GRN"%s\n"RESET, *tokens);
	int count;

	char **arguments;
	arguments = NULL;
	count = 0;
	arguments = init_args(ACTUAL_POSITION_IN_LEXER_RESULT);
	while(lexer_result[*current_token] && ft_strncmp(PIPE, lexer_result[*current_token], ft_strlen(PIPE)))
	{
		arguments[count] = ft_strdup(lexer_result[*current_token]);
		count++;
		(*current_token)++;
	}
	(*current_token)++;
	return (arguments);
}

/*
** функция которая собирает siple_command из токенов
*/

t_simple_command *get_simple_command(char **lexer_result, int *current_token)
{
	t_simple_command	*simple_command;	// один элемент массива simple_commands

	simple_command = simple_command_init(ACTUAL_POSITION_IN_LEXER_RESULT);		//выделить память и занулить
	simple_command->arguments = get_args(lexer_result, current_token);
//	simple_command->outfile = get_outfiles(lexer_result, current_token);
	return (simple_command);
}

/*
** функция которая собирает из simple_command command_table (simple_commands)
*/

t_command get_command_table(char **lexer_result)
{
	t_command			command;
	t_simple_command	**command_table;
	int 				last_token;
	int 				current_token;
	int 				count;

	count = 0;
	current_token = 0;
	last_token = ft_array_len(lexer_result);
	command_table = command_table_init(lexer_result);		//выделить память и занулить
	while(NOT_LAST_TOKEN)
	{
		command_table[count] = get_simple_command(lexer_result, &current_token);
		count++;
	}
	command.simple_commands = command_table;
	return (command);
}
