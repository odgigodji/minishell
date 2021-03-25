#include "minishell.h"

int ft_make_outfile(t_common *common, char *line, int increment, int current_out_file)
{

	int outfile_len;
	outfile_len = ft_strlen_to_char(line + increment, ' ');
	printf(BG_WHT"%s\n"RESET, line + increment);
	printf("OUTFILE LEN [%d]\n"RESET, (int)outfile_len);
	printf("CURRENT_OUT_FILE IS %d\n", current_out_file);

	common->command.simple_commands[common->command.current_simple_command]->out_file[current_out_file] = ft_calloc(sizeof(char), outfile_len + 1);
	ft_strlcat(common->command.simple_commands[common->command.current_simple_command]->out_file[current_out_file],\
	line + increment, outfile_len + 1); // +1 на \0
	printf("current simple command is %d\n", common->command.current_simple_command);
	printf(RED"[%s]\n"RESET, common->command.simple_commands[common->command.current_simple_command]->out_file[current_out_file]);
	current_out_file++;
	common->command.simple_commands[common->command.current_simple_command]->arg_count--;
	return (outfile_len);
}

int ft_do_outfile(t_common *common, char *line, int increment)
{
//	static int current_out_file = 0;
	int current_out_file;
	int num_of_outfiles;
	int ret;

	ret = 0;
	current_out_file = common->command.simple_commands[common->command.current_simple_command]->current_outfile;
	num_of_outfiles = common->command.simple_commands[common->command.current_simple_command]->num_of_outfiles;
	if (current_out_file == num_of_outfiles) // common->command.simple_commands[common->command.current_simple_command]->have_pipe ||
	{
		printf("CURRENT_OUT_FILE IS %d(should be 0)\n", current_out_file);
//		common->command.simple_commands[common->command.current_simple_command]->have_pipe = 0;

		ret = ft_make_outfile(common, line, increment, current_out_file);
		common->command.simple_commands[common->command.current_simple_command]->current_outfile = 0;
//		common->command.simple_commands[current_command]->out_file[num_of_outfile] = NULL;
		return (ret);
	}
	if (current_out_file != num_of_outfiles)
	{
		common->command.simple_commands[common->command.current_simple_command]->current_outfile++;
		current_out_file++;
		ret = ft_make_outfile(common, line, increment, current_out_file);
	}
	common->command.simple_commands[common->command.current_simple_command]->out_file[num_of_outfiles] = NULL;
	return (ret);
}

int do_redirect(t_common *common, char *line)
{
	int i;

	i = 0;
//	common->command.simple_commands[common->command.current_simple_command]->out_file[0] = "\0";//
	if (line[i] == '>')
	{
		printf("REDIR_start:|%s|\n", line + 1);
		i++;
		while(line[i] && line[i] != ';' && line[i] != '|')
		{
			if (line[i] == ' ' || line[i] == '\t') // такие единичные штуки надо как то нормально сделать с табами и пробелами
				i++;
			else
			{
				i += ft_do_outfile(common, line, i);
				return (i);
			}
		}
		printf("----->|%s|\n", common->command.simple_commands[common->command.current_simple_command]->out_file[0]);
//		common->command.simple_commands[common->command.current_simple_command]->out_file[0];
	}
	return 0;
}