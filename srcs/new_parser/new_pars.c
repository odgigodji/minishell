#include "minishell.h"

int is_spec(char *spec, char current_char)
{
	if(ft_strchr(spec, current_char))
		return (1);
	else
		return (0);
}

int line_to_arg(t_common *common, char *line)
{
	int i;
	char spec[11] = " '|\"$\t<>";

	i = 0;
	if (DEBUG)
		printf("line_to_arg:|%s|\n", line); //-------------------------------------------------
	while(line[i] && line[i] != ';')
	{
		if(is_spec(spec, line[i]))
		{
			i = do_all_spec(common, line + i, line[i], i);
//			if (i > ft_strlen(line))
//				return(i);
		}
		else
		{
			i = make_args(line, common,i); //если символ не равен спец символу прописываем аргументы
		}
	}
	if (line[i] == ';')
		i++;
//	common->command.simple_commands[common->command.current_simple_command]->\
//	arguments[common->command.simple_commands[common->command.current_simple_command]->arg_count] = NULL; // зануляем последний арг
//	printf(RED"<%s>\n"RESET, common->command.simple_commands[0]->arguments[0]); // я теряю где то элемент, надо искать
//	printf("I IS %d\n", i);
	return (i);
}

int new_pars(t_common *common, char *line)
{
	int current_position;

	if (DEBUG)
	{
		printf(YEL"---------------------------------------DEBUG_MOD-----------------------------------\n"RESET);
		printf("new_pars:|%s|\n", line);
	}
	common->command.current_simple_command = 0;
	common->command.space_after_redirect = 0;

	ft_init_current_command(common, line);			//инициализируем структуру симпл команды
	current_position = line_to_arg(common, line);
	if (FINAL_PRINT)
	{
//		ft_print_common(common, 1);
		printf(CYN"-----------------------------------------------------------end of parser----------------------------------------------------\n"RESET);
	}
	return (current_position); //считываем line и записываем все в simple_commands->arguments
}