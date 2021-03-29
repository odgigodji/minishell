#include "minishell.h"

int make_outfile_can(t_common *common, char *line, int increment, int current_outfile_can)
{
	printf("do redir\n");
	int outfile_can_len;
	outfile_can_len = ft_strlen_to_char(line + increment, ' '); //fixme длина до пробела или до другого спец символа

	if (DOUBLE_REDIR)
	{
		printf("ft_make_outfile:|%s|\n", line);
		printf(BG_WHT"%s\n"RESET, line + increment);
		printf("OUTFILE LEN [%d]\n"RESET, (int) outfile_can_len);
		printf("current simple command is %d\n", common->command.current_simple_command);
	}

	common->command.simple_commands[common->command.current_simple_command]->outfile_can[current_outfile_can] = ft_calloc(sizeof(char), outfile_can_len + 1);
	ft_strlcat(common->command.simple_commands[common->command.current_simple_command]->outfile_can[current_outfile_can],\
	line + increment, outfile_can_len + 1); // +1 на \0


//	current_out_file++;
	if (common->command.space_after_redirect) 							// fixme случай когда первый после '>' есть пробел тогда снижаем кол- во аргументов симпл команды
		common->command.simple_commands[common->command.current_simple_command]->arg_count--;
	return (outfile_can_len);
}

int do_outfile_can(t_common *common, char *line, int increment)
{
//	static int current_out_file = 0;
	int current_outfile_can;
	int num_of_outfiles_can;
	int ret;

	ret = 0;

	current_outfile_can = common->command.simple_commands[common->command.current_simple_command]->current_outfile_can;
	num_of_outfiles_can = common->command.simple_commands[common->command.current_simple_command]->num_of_outfiles_can;

	ret = make_outfile_can(common, line, increment, current_outfile_can);
	common->command.simple_commands[common->command.current_simple_command]->current_outfile_can++;

	common->command.simple_commands[common->command.current_simple_command]->outfile_can[num_of_outfiles_can] = NULL;


	if (DOUBLE_REDIR)
		printf(RED"[%s]\n"RESET, common->command.simple_commands[common->command.current_simple_command]->outfile_can[current_outfile_can]);
	return (ret);
}

int ft_double_redir(t_common *common, char *line)
{
	if (DOUBLE_REDIR)
		printf("--double redir:line is |%s|\n", line);
	int i = 1;
//	i++;
	printf("--double redir:line is |%s|\n", line + 1);
	while(line[i] && line[i] != ';' && line[i] != '|')
	{
		if (line[i] == ' ' || line[i] == '\t') // такие единичные штуки надо как то нормально сделать с табами и пробелами
		{
			common->command.space_after_redirect = 1;
			i++;
		}
		else
		{
			i += do_outfile_can(common, line, i);
			return (i);
		}
	}
	return 0;
}