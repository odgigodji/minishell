#include "minishell.h"

int ft_make_input_file(t_common *common, char *line, int increment)
{
	int input_file_len;
	input_file_len = ft_strlen_to_char(line + increment, ' '); //fixme длина до пробела или до другого спец символа

	if (DEBUG_INFILE)
	{
		printf("ft_make_outfile:|%s|\n", line);
		printf(BG_WHT"%s\n"RESET, line + increment);
		printf("INPUT LEN [%d]\n"RESET, (int) input_file_len);
		printf("current simple command is %d\n", common->command.current_simple_command);
	}

	common->command.infile = ft_calloc(sizeof(char), input_file_len + 1);
	ft_strlcat(common->command.infile,line + increment, input_file_len + 1); // +1 на \0


	if (common->command.space_after_redirect) 							// fixme случай когда первый после '>' есть пробел тогда снижаем кол- во аргументов симпл команды
		common->command.simple_commands[common->command.current_simple_command]->arg_count--;
	return (input_file_len);
}

int ft_do_input_file(t_common *common, char *line, int increment)
{
	int ret;

	if (DEBUG_INFILE)
	{
		printf(BLU"ft_do_input_file:line:|%s|\n"RESET, line + increment);
	}
	ret = ft_make_input_file(common, line, increment);

	if (DEBUG_INFILE)
		printf(RED"fin_input_file[%s]\n"RESET, common->command.infile);
	return (ret);
}

int do_reverse_redirect(t_common *common, char *line)
{
	int i;

	i = 1;
	if(DEBUG_INFILE)
	{
		printf(RED"do_rev_redir:|%s|\n"RESET, line);
		printf("REDIR_start:|%s|\n", line + 1);
	}
	while(line[i] && line[i] != ';' && line[i] != '|')
	{
		if (line[i] == ' ' || line[i] == '\t') // fixme такие единичные штуки надо как то нормально сделать с табами и пробелами
		{
			common->command.space_after_redirect = 1; //флаг который показывает если после знака редиректа пробел или таб
			i++;
		}
		else
		{
			i += ft_do_input_file(common, line, i);
			return (i);
		}
	}

	if (DEBUG_INFILE)
		printf(MAG"----->|%s|\n"RESET, common->command.infile);
//		common->command.simple_commands[common->command.current_simple_command]->out_file[0];

	return 0;
}