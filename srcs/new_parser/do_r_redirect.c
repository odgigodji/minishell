#include "minishell.h"

int ft_make_in(t_common *common, char *line, int increment, int current_infile)
{
//
	int infile_len;
	infile_len = ft_strlen_to_char(line + increment, ' '); //fixme длина до пробела или до другого спец символа

	if (DEBUG_INFILE)
	{
		printf("ft_make_infile:|%s|\n", line);
		printf(BG_WHT"%s\n"RESET, line + increment);
		printf("OUTFILE LEN [%d]\n"RESET, (int) infile_len);
		printf("CURRENT_OUT_FILE IS %d\n", current_infile);
		printf("current simple command is %d\n", common->command.current_simple_command);
	}

	common->command.simple_commands[common->command.current_simple_command]->infile[current_infile] = ft_calloc(sizeof(char), infile_len + 1);
	ft_strlcat(common->command.simple_commands[common->command.current_simple_command]->infile[current_infile],\
	line + increment, infile_len + 1); // +1 на \0


//	current_out_file++;
	if (common->command.space_after_redirect) 							// fixme случай когда первый после '>' есть пробел тогда снижаем кол- во аргументов симпл команды
		common->command.simple_commands[common->command.current_simple_command]->arg_count--;
	return (infile_len);
}

int ft_do_in(t_common *common, char *line, int increment)
{
//	static int current_out_file = 0;
	int current_infile;
	int num_of_infiles;
	int ret;

	ret = 0;

	current_infile = common->command.simple_commands[common->command.current_simple_command]->current_infile;
	num_of_infiles = common->command.simple_commands[common->command.current_simple_command]->num_of_infiles;
	if (current_infile != num_of_infiles)
	{
		ret = ft_make_in(common, line, increment, current_infile);
		common->command.simple_commands[common->command.current_simple_command]->current_infile++;

	}
//	common->command.simple_commands[common->command.current_simple_command]->infile[num_of_infiles] = NULL;


	if (DEBUG_INFILE)
		printf(RED"[%s]\n"RESET, common->command.simple_commands[common->command.current_simple_command]->infile[current_infile]);
	return (ret);
}

int do_r_redirect(t_common *common, char *line)
{
	int i;

	i = 0;
//	common->command.simple_commands[common->command.current_simple_command]->outfile[0] = "\0";//

	if (DEBUG_INFILE)
		printf("REDIR_start:|%s|\n", line + 1);

	i++;
	while(line[i] && line[i] != ';' && line[i] != '|')
	{
		if (line[i] == ' ' || line[i] == '\t') // такие единичные штуки надо как то нормально сделать с табами и пробелами
		{
			common->command.space_after_redirect = 1;
			i++;
		}
		else
		{
			i += ft_do_in(common, line, i);
			common->command.space_after_redirect = 0;  // fixme add
			return (i);
		}
	}

//		if (DEBUG_INFILE)
//			printf("----->|%s|\n", common->command.simple_commands[common->command.current_simple_command]->infile[0]);
//		common->command.simple_commands[common->command.current_simple_command]->outfile[0];
	return 0;
}