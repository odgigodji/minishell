#include "minishell.h"

int len_for_calloc(char *line, t_common *common, int increment, char *spec)
{
	int len_for_calloc;
	int i;

	i = increment;
//	printf("|%s|\n", line + i);
	len_for_calloc = 0;
	while(!ft_strchr(spec, line[i]))
	{
		len_for_calloc++; //cчитает и последнгий элемент тоже так как возвращает указзаткльно на нуль терминатор
		i++;
	}
//	printf("len after %d\n", len_for_calloc);
	return (len_for_calloc);
}

void ft_do_arg_and_switch_to_next_arg(t_common *common, char *res, int len_for_calloc)
{
	int current_command;

//	ft_init_next_struct(common);
	current_command = common->command.current_simple_command;

//	printf("number_of_arg is %d\n", common->command.simple_commands[0]->current_arg);
//	printf("res is %s\n", res);
//	printf(BLU"current command is %d\n"RESET, current_command);
//	printf(YEL"current arg is %d\n"RESET, common->command.simple_commands[current_command]->current_arg);

	common->command.simple_commands[current_command]->arguments[common->command.simple_commands[current_command]->current_arg] = ft_strdup(res);
//	printf(GRN"<%s>\n"RESET, common->command.simple_commands[current_command]->\
	arguments[common->command.simple_commands[current_command]->current_arg]);
	if (common->command.simple_commands[current_command]->current_arg != common->command.simple_commands[current_command]->arg_count)
		common->command.simple_commands[current_command]->current_arg++;
	else
		common->command.simple_commands[current_command]->current_arg = 0;
}

int do_arg(t_common *common, char *line, int len_for_calloc, int increment)
{
	char res[len_for_calloc + 1];
	int current_command = common->command.current_simple_command;
	int arg_count = common->command.simple_commands[current_command]->arg_count;

	ft_strlcpy(res, line + increment, len_for_calloc + 1); 	//записываем все символы до спец символа во временную строку res
	if (DEBUG)
	{
		printf("len for calloc is %d current line is [%s]\n", len_for_calloc, line + increment);
		printf("---%s---\n", res);
	}
	ft_do_arg_and_switch_to_next_arg(common, res, len_for_calloc);  //копируем res в simple_command->arguments
	common->command.simple_commands[current_command]->arguments[arg_count] = NULL;
	if (DEBUG)
	{
	printf("cur_arg is %d\n", common->command.simple_commands[current_command]->current_arg);

	printf(BLU"<%s>\n"RESET, common->command.simple_commands[current_command]->\
	arguments[common->command.simple_commands[current_command]->current_arg - 1]);
	}
	return (increment + len_for_calloc); // возвращаем позицию в нашей строке line изменненную на длину записанного аргумента
}

int	make_args(char *line, t_common *common, int increment)
{
	int len;
	char spec[] = " '|\"$\t;<>";
	if (DEBUG)
		printf("make_args line:|%s|\n", line);

	len = len_for_calloc(line, common, increment, spec); // высчитываем длину для выделения памяти
	do_arg(common, line, len, increment); // создаем аргумент

//	i += len;
//	printf("len_for_calloc is %d\n", len);
	return (increment + len);
}