#include "minishell.h"

void ft_printf_outfile_info(t_common *common)
{
	int current_sc = common->command.current_simple_command;
	printf(MAG"current_outfile:%d\n"RESET, common->command.simple_commands[current_sc]->current_outfile);
	printf(MAG"current_sc:%d\n"RESET, current_sc);
//	printf(MAG"current_outfile:%d\n"RESET, common->command.simple_commands[current_sc]->current_outfile);
}

void ft_init_next_simple_command(t_common *common, char *line)
{
	int current_command;//команда на которой мы сейяча находимся

//	printf(RED"line after '|' is <%s>\n"RESET, line);
//	printf("next_arg_count is %d\n", arg_count)
//	printf("->%d\n", arg_count);
	current_command = common->command.current_simple_command;
	ft_init_simple_commands(common, line, current_command);
	ft_init_outfiles(common, line, current_command);
//	common->command.simple_commands[common->command.current_simple_command]->have_pipe = 1;
}

void do_pipe(t_common *common, char *line)
{

	//		printf("current char is <%c>\n", curent_char);
	//		printf("current line is <%s>\n", line);
	if (common->command.current_simple_command != common->command.num_of_simple_commands)
		common->command.current_simple_command++; // если не последняя команда переключаеммся на следедующую
//		else
//			return (increment);
	ft_init_next_simple_command(common, line + 1); //инициализируем следующую команду
//	ft_printf_outfile_info(common);
}