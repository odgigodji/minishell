#include "minishell.h"

void ft_init_next_simple_command(t_common *common, char *line)
{
	int current_command;//команда на которой мы сейяча находимся
	int arg_count;

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

//	printf(BLU"arg_count for simple command[%d] is %d\n"RESET, current_command, common->command.simple_commands[current_command]->arg_count);
//	common->command.simple_commands[current_command]->current_arg = 0;
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

int do_redirect(t_common *common, char *line)
{
	int i = 0;
	common->command.simple_commands[common->command.current_simple_command]->out_file = ft_calloc(sizeof(char *), 5);
	common->command.simple_commands[common->command.current_simple_command]->out_file[0] = ft_calloc(sizeof(char), MAX_NAME); //
	if (line[i] == '>')
	{
		printf("|%s|\n", line + 1);
		i++;
		while(line[i] && line[i] != ';' && line[i] != '|')
		{
			if (line[i] == ' ')
				i++;
			else
			{
				printf(BG_WHT"%s\n"RESET, line + i);
				printf("");
//				ft_strlcat(common->command.simple_commands[common->command.current_simple_command]->out_file[0],\
				line + i, ft_strlen_to_char(line + i, ' '));
			   	return (i);
			}
//			i++;
		}
//		printf("----->|%s|\n", common->command.simple_commands[common->command.current_simple_command]->out_file[0]);
//		common->command.simple_commands[common->command.current_simple_command]->out_file[0];
	}
//	printf("RDRCT---\n");
	return i;
}

int do_all_spec(t_common *common, char *line, char current_char, int increment)
{
	if (current_char == '|')
		do_pipe(common, line); // делаем пайп
//	if (current_char == '>' || current_char == '<')
//		increment += do_redirect(common, line);
	increment++; //переходим на следующий элемент
//	printf("----->|%s|\n", common->command.simple_commands[common->command.current_simple_command]->out_file[0]);
	return (increment);
}