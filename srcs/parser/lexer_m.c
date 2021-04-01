//
// Created by Mariam Scot on 4/1/21.
//

//#include <stdio.h>
//#include <unistd.h>
//#include <stdlib.h>
//#include <string.h>
//
//# define SPEC_SYMBOL " '|\"\t<>"
////# define SPEC_SYMBOL " '|\"$\t<>"
//# define GREAT "<GREAT>"				// ">"
//# define GREATGREAT "<GREATGREAT>"		// ">>"
//# define LESS "<LESS>"					// "<"
//# define GREATLESS "<GREATLESS>"		// "<<"
//# define PIPE "<PIPE>"					// "|"
//# define VAR "<VAR>"					// "$"
//# define MAX_PATH 2048
#include "minishell.h"

//int				get_token(char *line, char **token);
///*
//** выделение памяти на simple_commands (simple_commands)
//*/
//
//t_simple_command	**command_table_init(int num_of_simple_commands)
//{
//	t_simple_command	**command_table; // называется simple_commands в нашей структуре
//	int 				count;
//
//	count = 0;
//	if (NULL == (command_table = malloc(sizeof(t_simple_command *) * (num_of_simple_commands + 1))))
//		return (NULL);
//	while (count < num_of_simple_commands)
//	{
//		command_table[count] = NULL;
//		count++;
//	}
//	return (command_table);
//}
//
///*
//** выделение памяти на одну simple_command (например на ["ls", "-l"])
//*/
//
//t_simple_command	*simple_command_init_m(void)
//{
//	t_simple_command	*simple_command;
//
//	simple_command = NULL;
//	return (simple_command);
//}
//
///*
//** функция которая по набору символов определяет являются ли они токеном
//** Например если в набор символов попал спец символ то строка перестает быть токеном
//** Пока символы не являются специальными это токен
//**
//** Возможно функция не очень подходящая её можно заменить на что-то ещё
//*/
//
//int					is_token(char *token)
//{
//	return (1);
//}
//
//
///*
//** Функция которая собирает simple_command из токенов
//*/
//
//t_simple_command	*get_simple_command(t_common *common, char *line)
//{
//	int					count;
//	t_simple_command	*simple_command;	// один элемент массива simple_commands
//	char				*token;
//
//	count = 0;
//	simple_command = simple_command_init_m();		//выделить память и занулить
//	while ((token = get_token(line)))
//	{
//		simple_command->arguments[count] = get_token(line);
//		count++;
//	}
//}
//
///*
//** функция которая собирает из simple_command command_table (simple_commands)
//*/
//
//int					get_command_table(t_common *common, char *line)
//{
//	t_command			command;
//	t_simple_command	**command_table;
//	t_simple_command	*simple_command;
//	int					count;
//
//	command_table = command_table_init(100);		//выделить память и занулить
//	simple_command = NULL;
//	count = 0;
//	while (NULL != (simple_command = get_simple_command(common, line)))
//	{
//		command_table[count] = simple_command;
//		count++;
//	}
//	command_table[count] = NULL;
//	common->command.simple_commands = command_table;
//	return (0);
//}

int			is_spec_symbol(char c)
{
	int	count;

	count = 0;
	while (SPEC_SYMBOL[count])
	{
		if (SPEC_SYMBOL[count] == c)
			return (1);
		count++;
	}
	return (0);
}

int			check_back_slash(char *line)
{
	int	count;

	count = 0;
	while (line[count] == '\\')
		count++;
	return (count);
}

/*
** функция которая бежит по строке и возвращается завалидированный токен
** По одному токену за один раз
*/

int			get_token(char *line, char **token)
{
	int		count_line;
	int		count_token;
	char	buffer[100];
	int		back_slash;
	int		back_slash_flag;
	char	brace_flag;

	count_line = 0;
	count_token = 0;
	back_slash_flag = 0;
	brace_flag = 0;
	buffer[0] = '\0';
//	while (line[count_line] && (line[count_line - 1] != '\\' && !is_spec_symbol(line[count_line])))
	while (line[count_line] && !is_spec_symbol(line[count_line]))
	{
//		if (line[count_line] == '\\')
//		{
//			back_slash = check_back_slash(&line[count_line]) / 2;
//			while (back_slash)
//			{
//				buffer[count_token] = '\\';
//				count_line += 2;
//				count_token++;
//				back_slash--;
//			}
//			if (line[count_line] == '\\')
//			{
//				back_slash_flag = 1;
////				count_line++;
//			}
//		}
		if (line[count_line] == '"' || line[count_line] == '\'')
		{
			brace_flag = line[count_line];
			while (brace_flag)
			{
				buffer[count_token] = line[count_line];
				count_line++;
				count_token++;
				if (line[count_line] == brace_flag)
					brace_flag = 0;
			}
		}
		if (line[count_line] && line[count_line] != ' '
		&& (!is_spec_symbol(line[count_line])
			|| (is_spec_symbol(line[count_line]) && back_slash_flag)))
		{
			buffer[count_token] = line[count_line];
			count_line++;
			count_token++;
		}
		else if (line[count_line] == ' ' || is_spec_symbol(line[count_line]))
		{
			break;
		}
		else
			count_line++;
		back_slash_flag = 0;
	}
	buffer[count_token] = '\0';
	*token = strdup(buffer);
	return (count_line);
}

char		*get_braced_token(char *line)
{
	int		count;
	char	*token;

	count = 0;
	if (NULL == (token = malloc(sizeof(char) * MAX_PATH)))
		return (NULL);
	token[count] = '\0';
	while (line[count])
	{
		token[count] = line[count];
		count++;
//		if (line[count] == ' ' && line[count - 1] != brace_type)
//		{
//			break ;
//		}
		if (((line[count] == '\'' || line[count] == '"') && line[count + 1] == ' ')
			|| line[count] == '\0')
		{
			token[count] = line[count];
			token[count + 1] = '\0';
			break ;
		}
	}
	return (token);
}

int			get_spec_token_length(char *line, char *token)
{
	if (line[0] == '|')
		return (1);
	else if (line[0] == '>')
	{
		if (line[1] != '>')
			return (1);
		else
			return (2);
	}
	else if (line[0] == '<')
	{
		if (line[1] != '<')
			return (1);
		else
			return (2);
	}
	else if (line[0] == '"' || line[0] == '\'')
		return ((int)strlen(token));
	return (0);
}

int			get_spec_token(char *line, char **token)
{
	char *a = SPEC_SYMBOL;

	if (line[0] == '|')
	{
		*token = strdup(PIPE);
	}
	else if (line[0] == '>')
	{
		if (line[1] != '>')
			*token = strdup(GREAT);
		else
			*token = strdup(GREATGREAT);
	}
	else if (line[0] == '<')
	{
		if (line[1] != '<')
			*token = strdup(LESS);
		else
			*token = strdup(GREATLESS);
	}
	else if (line[0] == '\'' || line[0] == '"')
		*token = get_braced_token(line);
	return (get_spec_token_length(line, *token));
}

char		**lexer(char *line)
{
	int		count;
	int		count_result;
	char	*token;
	char	**result;

	count = 0;
	count_result = 0;
	token = NULL;
	if (NULL == (result = malloc(sizeof(char *) * 100)))
		return (NULL);
	result[0] = NULL;
	while(line[count] && line[count] != ';')
	{
		if (!is_spec_symbol(line[count]))
			count += get_token(&line[count], &token);
		else
			if (line[count] != ' ')
				count += get_spec_token(&line[count], &token);
		if (token && token[0] != '\0')
		{
			result[count_result] = token;
			count_result++;
			result[count_result] = NULL;
		}
		if (line[count] == ' ' && '\0' != line[count])
			count++;
	}
	return (result);
}

//int	main(int argc, char **argv)
//{
//	char	**lexer_result;
//	int		count;
//
//	lexer_result = lexer(argv[1]);
//	count = 0;
//	while (lexer_result[count])
//	{
//		printf("[%3d] |%10s|\n", count, lexer_result[count]);
//		count++;
//	}
//	return (0);
//}






