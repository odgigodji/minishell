#include "minishell.h"

void ft_init_next_simple_command(t_common *common, char *line)
{
	int current_command;//команда на которой мы сейяча находимся
	int arg_count;
	int num_of_outfile;

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
	printf(BLU"redirect_count is %d\n"RESET, num_of_outfile);
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

int ft_init_out_or_input_file(t_common *common, char *line, int increment)
{
	static int current_out_file = 0;
	int num_of_outfiles;
	int outfile_len;

	num_of_outfiles = 2;
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

int do_all_spec(t_common *common, char *line, char current_char, int increment)
{
	if (current_char == '|')
		do_pipe(common, line); // делаем пайп
	if (current_char == '>' || current_char == '<')
		increment += do_redirect(common, line);
	increment++; //переходим на следующий элемент
	return (increment);
}