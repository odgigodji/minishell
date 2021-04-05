#include <tcl.h>
#include "minishell.h"

char **get_infiles(char **lexer_result)
{
	char **infiles;
	int counter;

	counter = 0;
	infiles = NULL;
	infiles = init_args(lexer_result, LESS);
	while(lexer_result && *lexer_result && ft_strcmp(*lexer_result, PIPE))
	{
		if(!ft_strcmp(*lexer_result, LESS))
		{
			if ((!(infiles[counter] = ft_strdup(*(++lexer_result)))))
				break ;
			counter++;
		}
		lexer_result++;
	}
	infiles[counter] = NULL;
	return(infiles);
}

char **get_outfiles(char **lexer_result, int *current_token)
{
	char **outfiles;
	int is_cat;

	int counter = 0;
	outfiles = NULL;
	outfiles = init_args(lexer_result, GREAT);
	while(lexer_result && *lexer_result && ft_strcmp(*lexer_result, PIPE))
	{
		if(!ft_strcmp(*lexer_result, GREAT) || !ft_strcmp(*lexer_result, GREATGREAT))
		{
//			if (!ft_strcmp(*lexer_result, GREATGREAT))
//				is_cat = 1;
			if ((!(outfiles[counter] = ft_strdup(*(++lexer_result)))))
				break ;
			counter++;
		}
		lexer_result++;
	}
	outfiles[counter] = NULL;
	return(outfiles);
}

void pass_redirect_files(char **lexer_result, int *current_token)
{
	char *token_after_file;

	token_after_file = lexer_result[*current_token + 2];
	if (!ft_strcmp(ACTUAL_TOKEN, GREAT) || !ft_strcmp(ACTUAL_TOKEN, GREATGREAT) || \
	!ft_strcmp(ACTUAL_TOKEN, LESS))
	{
		printf(MAG"-%d\n"RESET, *current_token);
		if (token_after_file && ft_strcmp(token_after_file, GREAT) || !token_after_file)
		{
			*current_token += 2;
			return ;
		}
		token_after_file = lexer_result[*current_token + 2];
		while (token_after_file && (!ft_strcmp(ACTUAL_TOKEN, GREAT) || !ft_strcmp(ACTUAL_TOKEN, LESS) \
		|| !ft_strcmp(ACTUAL_TOKEN, GREATGREAT)) \
		&& (!ft_strcmp(token_after_file, GREAT )|| !ft_strcmp(ACTUAL_TOKEN, LESS) \
		|| !ft_strcmp(ACTUAL_TOKEN, GREATGREAT)))
			*current_token += 2;
		printf(MAG"--%d\n"RESET, *current_token);
	}
}

char **get_args(char **lexer_result, int *current_token)
{
//	printf(GRN"%s\n"RESET, *tokens);
	int count;

	char **arguments;
	arguments = NULL;
	count = 0;
	arguments = init_args(ACTUAL_POSITION_IN_LEXER_RESULT, PIPE);
	while(ACTUAL_TOKEN && ft_strcmp(ACTUAL_TOKEN, PIPE))
	{
		pass_redirect_files(lexer_result, current_token);
		printf("=%s\n",ACTUAL_TOKEN);
		if (!(arguments[count] = ft_strdup(ACTUAL_TOKEN)))
			return (arguments);
		count++;
		(*current_token)++;
	}
	arguments[count] = NULL;
	(*current_token)++;
	return (arguments);
}

/*
** функция которая собирает siple_command из токенов
*/

t_simple_command *get_simple_command(char **lexer_result, int *current_token)
{
	t_simple_command	*simple_command;	// один элемент массива simple_commands

	simple_command = one_simple_command_init(ACTUAL_POSITION_IN_LEXER_RESULT);//выделить память и занулить
	if(*current_token > ft_array_len(lexer_result))
		return (simple_command);
	simple_command->outfiles = get_outfiles(ACTUAL_POSITION_IN_LEXER_RESULT, current_token);
	simple_command->infiles = get_infiles(ACTUAL_POSITION_IN_LEXER_RESULT);
	simple_command->arguments = get_args(lexer_result, current_token);
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
