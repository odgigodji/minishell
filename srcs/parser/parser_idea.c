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


t_simple_command *get_simple_command(char **tokens)
{
	int					count;
	t_simple_command	*simple_command;	// один элемент массива simple_commands
	char				*token;

//	ft_print_lexer_result(lexer_result);
	count = 0;
	simple_command = simple_command_init(tokens);		//выделить память и занулить
	while(tokens && tokens[count] && ft_strncmp(PIPE, *tokens, ft_strlen(PIPE)))
	{
		printf("actual token is {%s}\n", *tokens);
		simple_command->arguments[count] = ft_strdup(*tokens);
		count++;
		tokens++;
	}
	int i =0;
	while(simple_command->arguments[i])
	{
		printf("%s\n", simple_command->arguments[i]);
		i++;
	}
//	ft_print_args(simple_command->arguments);
	exit (5);
//	while ((token = token_to_simple_command(lexer_result[count])))
//	{
//		simple_command->arguments[count] = token;
//		count++;
//	}
//	simple_command->arguments[0] = "hello";
//	simple_command->arguments[1] = "world";
//	exit(0);
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
//	int					count;

	command.current_token = 0;
	command_table = command_table_init(lexer_result);		//выделить память и занулить
//	count = 0;
	command_table[0] = get_simple_command(lexer_result);

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
