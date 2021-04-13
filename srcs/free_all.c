#include "minishell.h"

void	free_lexer_results(char ***lexer_results)
{
	int count;

	count = 0;
	while ((*lexer_results)[count])
	{
		free((*lexer_results)[count]);
		count++;
	}
	free((*lexer_results)[count]);
	free(*lexer_results);
	*lexer_results = NULL;
}

void	free_argument_list(char ***list)
{
	int	count;

	count = 0;
	while ((*list)[count])
	{
		free((*list)[count]);
		count++;
	}
	free((*list)[count]);
	free(*list);
	*list = NULL;
}

void	free_simple_command(t_simple_command *simple_command)
{
	free_argument_list(&simple_command->arguments);
	free_argument_list(&simple_command->outfiles);
	free_argument_list(&simple_command->infiles);
	free(simple_command->outfiles);
	free(simple_command->infiles);
	free(simple_command->arguments);
}

void	free_command_table(t_common *common)
{
	t_simple_command	**command_table;
	int					count;

	count = 0;
	command_table = common->command.simple_commands;
	while (command_table[count])
	{
		free_simple_command(command_table[count]);
		free(command_table[count]);
		count++;
	}
	free(command_table[count]);
	free(common->command.simple_commands);
}