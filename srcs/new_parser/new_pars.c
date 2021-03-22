#include "minishell.h"

int line_to_arg(t_common *common, char *line)
{
	int i;

	i = 0;
	printf("|%s|\n", line); //-------------------------------------------------
	while(line[i] && line[i] != ';')
	{
//		printf("(%c)\n", line[i]);
		if (line[i] == ' ' || line[i] == '"' || line[i] == '\'' || line[i] == '\t' \
		|| line[i] == '|' || line[i] == '$')
		{
//			printf("curr char is >%c<\n", line[i]);
			i = do_all_spec(common, line + i, line[i], i);
//			printf("current simple command after do_spec is %d\n",common->command.current_simple_command);
		}
		else
		{
			i = make_args(line, common, i); //если символ не равен спец символу прописываем аргументы
		}
//		i++;
	}
	if (line[i] == ';')
		i++;
	common->command.simple_commands[common->command.current_simple_command]->\
	arguments[common->command.simple_commands[common->command.current_simple_command]->arg_count] = NULL; // зануляем последний арг
//	printf("I IS %d\n", i);
	return (i);
}

int	ft_arg_counter(char *s)																//fixme
{
//	printf(BG_WHT"string in ft_arg_counter +%s+\n"RESET, s);
	int		count;
	int 	quote_t;
	int		c;

	c = ' ';
	count = 0;
	while ((*s && *s != '|' && *s!= ';') || (*s == c && *s + 1 == '|'))
	{
//		if ((*s == '"' || *s == '\''))// && *(s - 1) != '\\')
//		{
//			count++;
//			quote_t = *s;
//			s++;
//			while(*s != quote_t)
//			{
//				s++;
//			}
//			s++;
//		}
		if ((*s != c && *(s + 1) == c) || (*s != c && (*(s + 1) == '\0')) || \
		(*s != c && (*(s + 1 ) == '|')) || (*s != c && (*(s + 1 ) == ';')))
			count++;
		s++;
	}
	return (count);
}

int ft_simple_command_counter(char *line) //fixme need upgrade
{
	int counter;

	counter = 1;
	while(*line && *line != ';')
	{
		if (*line == '|')
			counter++;
		line++;
	}
	return (counter);
}

void ft_init_struct(t_common *common, char *line)
{
	int current_command;
	int arg_count;
	int simple_command_count;

	current_command = common->command.current_simple_command;
	arg_count = ft_arg_counter(line);	//считаем аргументы симпл команды
//	printf("->%d\n", arg_count);
	simple_command_count = ft_simple_command_counter(line);
	common->command.simple_commands = ft_calloc(sizeof(t_simple_command *), simple_command_count + 1); // пять команд это типо если будут пайпы  fixme
	common->command.simple_commands[current_command] = ft_calloc(sizeof(t_simple_command) , 1); //одна команда без пайпов
	common->command.simple_commands[current_command]->arguments = ft_calloc(sizeof(char *),arg_count + 1);
	common->command.simple_commands[current_command]->current_arg = 0;//задаем номер текущего аргумента = 0 тк как формируем новый массив аргументов
	common->command.simple_commands[current_command]->arg_count = arg_count; // количество аргуемнтов заносим в структуру
//	printf(BLU"arg_count for 0 simple command is %d\n"RESET, common->command.simple_commands[current_command]->arg_count);
	common->command.number_of_simple_commands = simple_command_count;

	printf(GRN"----------------command.number_of_simple_commands is %d------------------\n"RESET, common->command.number_of_simple_commands);

//	common->command.number_of_simple_commands = 3; 	//	fixme количество симпл команд
	common->command.simple_commands[simple_command_count] = NULL;
	common->command.simple_commands[0]->arguments[arg_count] = NULL;
	common->command.current_simple_command = 0;
	;
}

int new_pars(t_common *common, char *line)
{
//	printf("------используется новый парсер, чтобы вернуться на старый нужно закомитить new_pars в parser.c и раскомитьть pars---------\n");
//	int arg_count;

	ft_init_struct(common, line);			//инициализируем структуру симпл команды
//	printf(BLU"current simple command is %d\n"RESET, common->command.current_simple_command);
//	common->command.simple_commands[0]->arg_count = arg_count; //записываем количество аргуметов в simple_command

//	printf("arg_count is %d\n", common->command.simple_commands[0]->arg_count);

	return(line_to_arg(common, line)); //считываем line и записываем все в simple_commands->arguments

}