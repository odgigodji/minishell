#include "minishell.h"

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

t_simple_command	*get_simple_command(t_common *common, char **lexer_result)
{
	int					count;
	t_simple_command	*simple_command;	// один элемент массива simple_commands
	char				*token;

	ft_print_lexer_result(lexer_result);
	count = 0;
	simple_command = simple_command_init(lexer_result);		//выделить память и занулить
	while(lexer_result && lexer_result[count] && TOKEN_IS_NOT_PIPE)
	{
		simple_command->arguments[count] = lexer_result[count];
		count++;
	}
//	ft_print_args(simple_command->arguments);
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

t_command			get_command_table(t_common *common, char **lexer_result)
{
	t_command			command;
	t_simple_command	**command_table; //simple_commands
	t_simple_command	*simple_command; //one simple_command
//	int					count;

	command_table = command_table_init(lexer_result);		//выделить память и занулить
//	count = 0;
	while ((simple_command = get_simple_command(common, lexer_result)))
	{
//		exit (0);
		*command_table = simple_command;
//		ft_print_args(*(command_table->arguments));
		command_table++;
	}
	command.simple_commands = command_table;
	return (command);
}
