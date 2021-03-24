#include "minishell.h"

int ft_init_out_or_input_file(t_common *common, char *line, int increment)
{
	static int current_out_file = 0;
	int num_of_outfiles;
	int outfile_len;

	num_of_outfiles = common->command.simple_commands[common->command.current_simple_command]->outfile_count;
	outfile_len = ft_strlen_to_char(line + increment, ' ');
	printf(BG_WHT"%s\n"RESET, line + increment);
	printf("BG_WHT[%d]\n"RESET, (int)outfile_len);
	printf("CURRENT_OUT_FILE IS %d\n", current_out_file);


	if (common->command.simple_commands[common->command.current_simple_command]->have_pipe && current_out_file == num_of_outfiles)
	{
		current_out_file = 0;
		printf("CURRENT_OUT_FILE IS %d(should be 0)\n", current_out_file);
		common->command.simple_commands[common->command.current_simple_command]->have_pipe = 0;

		common->command.simple_commands[common->command.current_simple_command]->out_file[current_out_file] = ft_calloc(sizeof(char), outfile_len + 1);
		ft_strlcat(common->command.simple_commands[common->command.current_simple_command]->out_file[current_out_file],\
	line + increment, outfile_len + 1); // +1 на \0
		printf("current simple command is %d\n", common->command.current_simple_command);
		printf(RED"[%s]\n"RESET, common->command.simple_commands[common->command.current_simple_command]->out_file[current_out_file]);
		current_out_file++;
		common->command.simple_commands[common->command.current_simple_command]->arg_count--;
//		common->command.simple_commands[current_command]->out_file[num_of_outfile] = NULL;
		common->command.simple_commands[common->command.current_simple_command]->out_file[current_out_file] = NULL;
		return (outfile_len);
	}
	if (current_out_file != num_of_outfiles)
	{
		common->command.simple_commands[common->command.current_simple_command]->out_file[current_out_file] = ft_calloc(sizeof(char), outfile_len + 1);
		ft_strlcat(common->command.simple_commands[common->command.current_simple_command]->out_file[current_out_file],\
	line + increment, outfile_len + 1); // +1 на \0
		printf("current simple command is %d\n", common->command.current_simple_command);
		printf(RED"[%s]\n"RESET, common->command.simple_commands[common->command.current_simple_command]->out_file[current_out_file]);
		current_out_file++;
		common->command.simple_commands[common->command.current_simple_command]->arg_count--;
	}

	return (outfile_len);
}

int do_redirect(t_common *common, char *line)
{
	int i;
	int outfile_len;

	i = 0;

//	common->command.simple_commands[common->command.current_simple_command]->out_file[0] = "\0";//
	if (line[i] == '>')
	{
		printf("|%s|\n", line + 1);
		i++;
		while(line[i] && line[i] != ';' && line[i] != '|')
		{
			if (line[i] == ' ' || line[i] == '\t') // такие единичные штуки надо как то нормально сделать с табами и пробелами
				i++;
			else
			{
				i += ft_init_out_or_input_file(common, line, i);
				return (i);
			}
//			i++;
		}
//		printf("----->|%s|\n", common->command.simple_commands[common->command.current_simple_command]->out_file[0]);
//		common->command.simple_commands[common->command.current_simple_command]->out_file[0];
	}
//	printf("RDRCT---\n");
	return 0;
}