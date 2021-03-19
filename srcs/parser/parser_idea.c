#include "minishell.h"

/*
** выделение памяти на simple_commands (simple_commands)
*/

t_simple_command	**command_table_init(void)
{
	t_simple_command	**command_table; // называется simple_commands в нашей структуре

	command_table = NULL; // выделить память и занулить переменные
	return (command_table);
}

/*
** выделение памяти на одну simple_command (например на ["ls", "-l"])
*/

t_simple_command	*simple_command_init(void)
{
	t_simple_command	*simple_command;

	simple_command = NULL;
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

char				*get_token(char *line)
{
	int		count;
	char	*token;

	count = 0;
	token = NULL;
	while (line[count])
	{
		if (is_token(token))
		{
			return (token);
		}
		count++;
	}
	return (token);
}

/*
** Функция которая собирает simple_command из токенов
*/

t_simple_command	*get_simple_command(t_common *common, char *line)
{
	int					count;
	t_simple_command	*simple_command;	// один элемент массива simple_commands
	char				*token;

	count = 0;
	simple_command = simple_command_init();		//выделить память и занулить
	while ((token = get_token(line)))
	{
		simple_command->arguments[count] = get_token(line);
		count++;
	}
}

/*
** функция которая собирает из simple_command command_table (simple_commands)
*/

t_command			get_command_table(t_common *common, char *line)
{
	t_command			command;
	t_simple_command	**command_table;
	t_simple_command	*simple_command;
	int					count;

	command_table = command_table_init();		//выделить память и занулить
	simple_command = NULL;
	count = 0;
	while ((simple_command = get_simple_command(common, line)))
	{
		command_table[count] = simple_command;
		count++;
	}
	command.simple_commands = command_table;
	return (command);
}
