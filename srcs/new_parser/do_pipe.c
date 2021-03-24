#include "minishell.h"

void ft_init_next_simple_command(t_common *common, char *line)
{
	int current_command;//команда на которой мы сейяча находимся
	int arg_count;
	int num_of_outfile;

	num_of_outfile = 0;
//	printf(RED"line after '|' is <%s>\n"RESET, line);
	arg_count = ft_arg_counter(line);	//считаем аргументы симпл команды
//	printf("next_arg_count is %d\n", arg_count)
//	printf("->%d\n", arg_count);
	current_command = common->command.current_simple_command;

	common->command.simple_commands[current_command] = ft_calloc(sizeof(t_simple_command) , 1); //одна команда без пайпов
	common->command.simple_commands[current_command]->arguments = ft_calloc(sizeof(char *),arg_count + 10);
	common->command.simple_commands[current_command]->arg_count = arg_count;  //кол во аргументов для новой симпл команды  fixme
	common->command.simple_commands[current_command]->current_arg = 0;
//	common->command.simple_commands[current_command]->arguments[arg_count] = NULL; //
	common->command.simple_commands[common->command.current_simple_command]->have_pipe = 1;
//	printf(BLU"arg_count for simple command[%d] is %d\n"RESET, current_command, common->command.simple_commands[current_command]->arg_count);
//	common->command.simple_commands[current_command]->current_arg = 0;

	num_of_outfile = ft_redirect_counter(line, '>');
	common->command.simple_commands[current_command]->out_file = ft_calloc(sizeof(char *), num_of_outfile); //fixme функция для этого
	common->command.simple_commands[current_command]->out_file[num_of_outfile] = NULL;

	common->command.simple_commands[current_command]->outfile_count = num_of_outfile;
	printf(BLU"redirect_count is %d\n"RESET, common->command.simple_commands[current_command]->outfile_count);
}

void do_pipe(t_common *common, char *line)
{
	//		printf("current char is <%c>\n", curent_char);
	//		printf("current line is <%s>\n", line);
	if (common->command.current_simple_command != common->command.number_of_simple_commands)
		common->command.current_simple_command++; // если не последняя команда переключаеммся на следедующую
//		else
//			return (increment);
	ft_init_next_simple_command(common, line + 1); //инициализируем следующую команду
}