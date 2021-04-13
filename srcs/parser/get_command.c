#include "minishell.h"

char	**get_args(char **lexer_result, int *current_token)
{
	int		count;
	char	**arguments;

	arguments = NULL;
	count = 0;
	arguments = init_args((lexer_result + *current_token), PIPE);
	while (lexer_result[*current_token] && ft_strcmp(lexer_result[*current_token], PIPE))
	{
		pass_redirect_files(lexer_result, current_token);
		if (lexer_result[*current_token] && (!ft_strcmp(lexer_result[*current_token], PIPE)))
			break ;
		arguments[count] = ft_strdup(lexer_result[*current_token]);
		if (!arguments[count])
			return (arguments);
		count++;
		(*current_token)++;
	}
	arguments[count] = NULL;
	(*current_token)++;
	return (arguments);
}

/*
** функция которая собирает simple_command из токенов
*/

t_simple_command	*get_simple_command(char **lexer_result, int *current_token)
{
	t_simple_command	*simple_command;

	simple_command = one_simple_command_init((lexer_result + *current_token));
	if (*current_token > ft_array_len(lexer_result))
		return (simple_command);
	simple_command->outfiles = get_outfiles(
			(lexer_result + *current_token), &simple_command->is_cat);
	simple_command->infiles = get_infiles((lexer_result + *current_token));
	simple_command->arguments = get_args(lexer_result, current_token);
	return (simple_command);
}

/*
** функция которая собирает из simple_command command_table (simple_commands)
*/

t_command	get_command_table(char **lexer_result)
{
	t_command			command;
	t_simple_command	**command_table;
	int					last_token;
	int					current_token;
	int					count;

	count = 0;
	current_token = 0;
	last_token = ft_array_len(lexer_result);
	command_table = command_table_init(lexer_result);
	while (current_token < last_token)
	{
		if (current_token >= ft_array_len(lexer_result))
			break ;
		command_table[count] = get_simple_command(lexer_result, &current_token);
		count++;
	}
	command.simple_commands = command_table;
	return (command);
}
