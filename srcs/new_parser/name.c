#include "minishell.h"

t_simple_command *get_simple_command1(char **lexer_result, int *current_token)
{
	t_simple_command	*simple_command;// один элемент массива simple_commands
	int files_count;
	int arg_count;
	int last_token;


//	last_token = ft_array_len(lexer_result);
	if(*lexer_result == NULL)
		return(NULL);
	files_count = 0;
	arg_count = 0;
	simple_command = one_simple_command_init(ACTUAL_POSITION_IN_LEXER_RESULT);//выделить память и занулить
	printf(GRN"%s\n"RESET, lexer_result[*current_token]);
	simple_command->outfiles = init_args(lexer_result, GREAT);
	simple_command->arguments = init_args(lexer_result, "regular_token");

	while(ACTUAL_TOKEN)
	{
		printf("-%s\n", ACTUAL_TOKEN);
//		if (!ft_strcmp(ACTUAL_TOKEN, PIPE))
//		{
//			*current_token += 1;
//			return (simple_command);
//		}
//		if(*current_token > ft_array_len(lexer_result))
//			return (simple_command);
//		if(!ft_strcmp(ACTUAL_TOKEN, GREAT))//is_redirect)
//		{
//			simple_command->outfiles[files_count] = ft_strdup(lexer_result[++(*current_token)]);//get_files;
//			printf(BLU"files:%s\n"RESET, simple_command->outfiles[files_count]);
//			if(simple_command->outfiles[files_count + 1])
//				files_count++;
//		}
//		if(ft_strcmp(ACTUAL_TOKEN, GREAT))//is-args_token
//		{
//			simple_command->arguments[arg_count] = ft_strdup(lexer_result[++(*current_token)]);//get_args
//			printf(RED"files:%s\n"RESET, simple_command->arguments[arg_count]);
//			if(simple_command->arguments[files_count + 1])
//				arg_count++;
//		}
		if(!lexer_result[*current_token + 1])
			break;
		else
			(*current_token)++;
	}
	simple_command->outfiles[files_count] = NULL;
	simple_command->arguments[files_count] = NULL;
	lexer_result[*current_token] = NULL;
	return (simple_command);
}
