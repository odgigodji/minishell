#include "minishell.h"

void ft_init_next_simple_command(t_common *common, char *line)
{
	int current_command;
	int arg_count;

	printf(RED"line after '|' is <%s>\n"RESET, line);
	arg_count = ft_arg_counter(line);	//считаем аргументы симпл команды
//	printf("next_arg_count is %d\n", arg_count)
	printf("->%d\n", arg_count);
	current_command = common->command.current_simple_command;

	common->command.simple_commands[current_command] = ft_calloc(sizeof(t_simple_command) , 1); //одна команда без пайпов
//	common->command.simple_commands[current_command]->arg_count = 3;//ft_arg_counter(line);//3;   //кол во аргументов для новой симпл команды  fixme

	common->command.simple_commands[current_command]->arguments = ft_calloc(sizeof(char *),arg_count + 1);
	common->command.simple_commands[current_command]->arg_count = arg_count;
	common->command.simple_commands[current_command]->current_arg = 0;
//	common->command.simple_commands[current_command]->current_arg = 0;
}

void ft_do_arg_and_switch_to_next_arg(t_common *common, char *res, int len_for_calloc)
{
	int current_command;

//	ft_init_next_struct(common);
	current_command = common->command.current_simple_command;
//	printf("number_of_arg is %d\n", common->command.simple_commands[0]->current_arg);
//	printf("res is %s\n", res);
	printf(BLU"current command is %d\n"RESET, current_command);
	printf(YEL"current arg is %d\n"RESET, common->command.simple_commands[current_command]->current_arg);
	common->command.simple_commands[current_command]->arguments[common->command.simple_commands[current_command]->current_arg] = ft_strdup(res);
//	printf(GRN"<%s>\n"RESET, common->command.simple_commands[0]->arguments[common->command.simple_commands[0]->current_arg]);
	if (common->command.simple_commands[current_command]->current_arg != common->command.simple_commands[current_command]->arg_count)
		common->command.simple_commands[current_command]->current_arg++;
}

int do_arg(t_common *common, char *line, int len_for_calloc, int increment)
{
	char res[len_for_calloc + 1];

	ft_strlcpy(res, line + increment, len_for_calloc + 1); 	//записываем все символы до спец символа во временную строку res
//	printf("len for calloc is %d current line is [%s]\n", len_for_calloc, line + increment);
	printf("---%s---\n", res);
	ft_do_arg_and_switch_to_next_arg(common, res, len_for_calloc);  //копируем res в simple_command->arguments
	return (increment + len_for_calloc); // возвращаем позицию в нашей строке line изменненную на длину записанного аргумента
}

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

int ft_test_shit(int k)
{
	k++;
	return(k);
}

int	make_args(char *line, t_common *common, int increment)
{
	int len;
	char spec[7] = " '|\"$\t";

	len = len_for_calloc(line, common, increment, spec); // высчитываем длину для выделения памяти
	do_arg(common, line, len, increment); // создаем аргумент
//	i += len;
//	printf("len_for_calloc is %d\n", len);
	return (increment + len);
}

int do_spec(t_common *common, char *line, char curent_char, int increment)
{
	if (curent_char == '|')
	{
		printf("current char is <%c>\n", curent_char);
		printf("current line is <%s>\n", line);
		common->command.current_simple_command++;
		ft_init_next_simple_command(common, line + 1);
	}
	increment++;
	return (increment);
}

void line_to_arg(t_common *common, char *line)
{
	int i;

	i = 0;
	printf("|%s|\n", line);
	while(line[i] && line[i] != ';')
	{
//		printf("(%c)\n", line[i]);
		if (line[i] == ' ' || line[i] == '"' || line[i] == '\'' || line[i] == '\t' \
		|| line[i] == '|' || line[i] == '$')
		{
//			printf("curr char is >%c<\n", line[i]);
			i = do_spec(common, line + i, line[i], i);
//			printf("current simple command after do_spec is %d\n",common->command.current_simple_command);
		}
////			common->command.current_simple_command++;
		else
		{
			i = make_args(line, common, i); //если символ не равен спец символу прописываем аргументы
		}
//		i++;
	}
	common->command.simple_commands[common->command.current_simple_command]->\
	arguments[common->command.simple_commands[common->command.current_simple_command]->arg_count] = NULL; // зануляем последний арг
}

int	ft_arg_counter(char *s)																//fixme
{
	int		count;
	int 	quote_t;
	int		c;

	c = ' ';
	count = 0;
	while (*s && *s != '|')
	{
		if ((*s == '"' || *s == '\''))// && *(s - 1) != '\\')
		{
			count++;
			quote_t = *s;
			s++;
			while(*s != quote_t)
			{
				s++;
			}
			s++;
		}
		if ((*s != c && *(s + 1) == c) || (*s != c && (*(s + 1) == '\0')))
			count++;
		s++;
	}
	return (count);
}

void ft_init_struct(t_common *common, char *line)
{
	int current_command;
	int arg_count;

	arg_count = ft_arg_counter(line);	//считаем аргументы симпл команды
	printf("->%d\n", arg_count);
	current_command = common->command.current_simple_command;
	common->command.simple_commands = ft_calloc(sizeof(t_simple_command *), 5); // пять команд это типо если будут пайпы  fixme
//	common->command.current_simple_command = 0;
	common->command.simple_commands[current_command] = ft_calloc(sizeof(t_simple_command) , 1); //одна команда без пайпов
	common->command.simple_commands[current_command]->arguments = ft_calloc(sizeof(char *),arg_count + 1);
	common->command.simple_commands[current_command]->current_arg = 0;
	common->command.simple_commands[current_command]->arg_count = arg_count;
	printf("arg_count is %d\n", common->command.simple_commands[current_command]->arg_count = arg_count);

//	common->command.simple_commands[1] = ft_calloc(sizeof(t_simple_command) , 1); //одна команда без пайпов
//	common->command.simple_commands[1]->arguments = ft_calloc(sizeof(char *),arg_count + 1);
//	common->command.simple_commands[1]->current_arg = 0;
	common->command.number_of_simple_commands = 3; //	fixme количество симпл команд

//	common->command.simple_commands[0]->arguments[arg_count] = NULL;
	;
}

void new_pars(t_common *common, char *line)
{
	printf("------используется новый парсер, чтобы вернуться на старый нужно закомитить new_pars в parser.c и раскомитьть pars---------\n");
//	int arg_count;

	ft_init_struct(common, line);			//инициализируем структуру симпл команды
	printf(BLU"current simple command is %d\n"RESET, common->command.current_simple_command);
//	common->command.simple_commands[0]->arg_count = arg_count; //записываем количество аргуметов в simple_command

	printf("arg_count is %d\n", common->command.simple_commands[0]->arg_count);

	line_to_arg(common, line); //считываем line и записываем все в simple_commands->arguments

}