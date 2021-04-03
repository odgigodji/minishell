#include <tcl.h>
#include "minishell.h"



/*
** функция которая по набору символов определяет являются ли они токеном
** Например если в набор символов попал спец символ то строка перестает быть токеном
** Пока символы не являются специальными это токен
**
** Возможно функция не очень подходящая её можно заменить на что-то ещё
*/

int					is_token(char *token)
{
	return (1);
}

/*
** функция которая бежит по строке и возвращается завалидированный токен
** По одному токену за один раз
*/

char				*token_to_simple_command(char *token_to_arg)
{
	int		count;
	char	*token;

	printf(YEL"%s\n"RESET, token_to_arg);
//	if (is_token(token))
//	{
//		return (token);
//	}
//	count = 0;
//	token = NULL;
//	while (token_to_arg[count])
//	{
//		if (is_token(token))
//		{
//			return (token);
//		}
//		count++;
//	}
	return (token);
}

/*
** Функция которая собирает simple_command из токенов
*/

char **get_args(char **tokens, int *current_token)
{
	printf(GRN"%s\n"RESET, *tokens);
	int count;

	char **arguments;
	count = 0;
	arguments = init_args(TOKENS_POSITION);
	while(tokens[*current_token] && ft_strncmp(PIPE, tokens[*current_token], ft_strlen(PIPE)))
	{
		printf("actual token is {%s}\n", tokens[*current_token]);
		arguments[count] = ft_strdup(tokens[*current_token]);
		count++;
		(*current_token)++;
	}
	(*current_token)++;
	return (arguments);
}

t_simple_command *get_simple_command(char **tokens, int *current_token)
{
	t_simple_command	*simple_command;	// один элемент массива simple_commands

	printf(BLU"[%d]\n"RESET, *current_token);
//	if(*current_token == ft_array_len(tokens))
//		return (NULL);
	simple_command = simple_command_init(TOKENS_POSITION);		//выделить память и занулить
	simple_command->arguments = get_args(tokens, current_token);
//	*current_token += ++count;echo 1 2 3 | echo 3 4 5 | ls -l -a
	printf(BLU"[%d]\n"RESET, *current_token);

	return (simple_command);
}

/*
** функция которая собирает из simple_command command_table (simple_commands)
*/

t_command get_command_table(char **lexer_result)
{
	t_command			command;
	t_simple_command	**command_table; //simple_commands
//	t_simple_command	*simple_command; //one simple_command
	int					counter;
	int 				last_token;

	counter = 0;
	int current_token = 0;
	command.current_token = 0;
	last_token = ft_array_len(lexer_result);
	command_table = command_table_init(lexer_result);		//выделить память и занулить
//	count = 0;
//	command_table[0] = get_simple_command(lexer_result, &command);
//	printf("current token is %d\n", command.current_token);
//	command_table[1] = get_simple_command(lexer_result + command.current_token, &command);
//	printf("current token is %d\n", command.current_token);
//	command_table[2] = get_simple_command(lexer_result + command.current_token, &command);
//	printf("current token is %d\n", command.current_token);

	while(NOT_LAST_TOKEN) //&& (command_table[counter] = get_simple_command(lexer_result, &current_token)))
	{
		command_table[counter] = get_simple_command(lexer_result, &current_token);
//		command_table[counter] = get_simple_command(lexer_result + current_token, &current_token);
		ft_print_simple_comand(command_table[counter]);
		counter++;
	}

//	exit(0);
//	while ((simple_command = get_simple_command(common, lexer_result)))
//	{
////		exit (0);
//		*command_table = simple_command;
////		ft_print_args(*(command_table->arguments));
//		command_table++;
//	}


	command.simple_commands = command_table;
	return (command);
}
