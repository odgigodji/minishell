#include "minishell.h"

void ft_do_arg_and_switch_to_next_arg(t_common *common, char *res)
{
	printf("number_of_arg is %d\n", common->command.simple_commands[0]->arg_number);
//	nubmer_of_arg = 0;
	common->command.simple_commands[0]->arguments[common->command.simple_commands[0]->arg_number] = res;
	if (common->command.simple_commands[0]->arg_number != common->command.simple_commands[0]->command_count)
		common->command.simple_commands[0]->arg_number++;
}

int do_arg(t_common *common, char *line, int len_for_calloc, int increment)
{
	char *res;
	int i;
	t_simple_command sc;
//	common->command.simple_commands[0]->arguments = ft_calloc(sizeof(char *), 2);
//	common->command.simple_commands[0]->arguments[0] = ft_calloc(sizeof(char), len_for_calloc + 1);
	i = 0;
//	static int k = 0;
	res = ft_calloc(sizeof(char), len_for_calloc + 1);
	while(len_for_calloc--)
	{
		res[i] = line[increment];
		i++;
		increment++;
	}
	printf("---%s---\n", res);
//	sc.arguments[0] = res;
//	printf("%s\n", sc.arguments[0]);
	i = 0;

	ft_do_arg_and_switch_to_next_arg(common, res);
	common->command.simple_commands[0]->arguments[common->command.simple_commands[0]->command_count] = NULL;
//	common->command.simple_commands[0]->arguments[0] = res;

//	printf("<%s>\n", common->command.simple_commands[0]->arguments[0]);
//	printf("<%s>\n", common->command.simple_commands[0]->arguments[1]);
//	printf("<%s>\n", common->command.simple_commands[0]->arguments[2]);

//	printf("%s\n", common->command.simple_commands[0]->arguments[0]);
//	if (common->command.simple_commands[0]->k != common->command.simple_commands[0]->command_count)
//		k++;
	return (increment);
}

int len_for_calloc(char *line, t_common *common, int increment, char *spec)
{
	int len_for_calloc;
	int i;

	i = increment;
//	printf("|%s|\n", line + i);
	len_for_calloc = 0;
//	len_for_calloc = ft_strlen_to_char(line + common->command.simple_commands[0]->i, ' ');
//	len_for_calloc = ft_strlen_to_char(line + common->command.simple_commands[0]->i, '"');
	while(!ft_strchr(spec, line[i]))
	{
		len_for_calloc++; //cчитает и последнгий элемент тоже так как возвращает указзаткльно на нуль терминатор
		i++;
	}
//	if (common->command.simple_commands[0]->k == common->command.simple_commands[0]->command_count)
//		len_for_calloc = ft_strlen(line + i);
//	else
//		common->command.simple_commands[0]->k++;
//	printf("len_for_calloc is %d\n", len_for_calloc);
	return (len_for_calloc);
}

int ft_test_shit(int k)
{
	k++;
	return(k);
}

int	make_args(char *line, t_common *common, int increment)
{
	int i;
	int len;
	char spec[6] = " '|\"$";

	i = increment;
	common->command.simple_commands[0]->arguments = ft_calloc(sizeof(char *),\
	common->command.simple_commands[0]->command_count + 1);
	len = len_for_calloc(line, common, i, spec);
	do_arg(common, line, len, i);
	i += len;
//	printf("len_for_calloc is %d\n", len);
	return (i);
}

void line_to_arg(t_common *common, char *line)
{
	int i;

	i = 0;
//	common->command.simple_commands[0] = malloc(sizeof(t_simple_command) * 1);
//	common->command.simple_commands[0]->k = 0;
//	common->command.simple_commands[0]->command_count = 3; // command count
	printf("|%s|\n", line);
	while(line[i] && line[i] != ';')
	{
		if (line[i] == ' ' || line[i] == '"' || line[i] == '\'' || line[i] == '\t' \
		|| line[i] == '|' || line[i] == '$')
			;
		else
		{
//			make_arg(line, common->command.simple_commands[0]);
			i = make_args(line, common, i);
//			printf("%c", line[i]);
		}
		i++;
	}
}

int	ft_arg_counter(char *s)												//fixme
{
	int		count;
	int 	quote_t;
	int		c;

	c = ' ';
	count = 0;
	while (*s)
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

void ft_init_struct(t_common *common)
{
	common->command.simple_commands = malloc(sizeof(t_simple_command *) * 5); // пять команд это типо если будут пайпы
	common->command.simple_commands[0] = ft_calloc(sizeof(t_simple_command) , 1); //одна команда без пайпов
	common->command.simple_commands[0]->arg_number = 0;
	;
}

void new_pars(t_common *common, char *line)
{
	printf("------используется новый парсер, чтобы вернуться на старый нужно закомитить new_pars в parser.c и раскомитьть pars---------\n");
	char **arg;
	int i;
	static int k = 0; // number of argument

	i = 0;

	int arg_count = ft_arg_counter(line);										//fixme написать функцию счетчика аргументов
	ft_init_struct(common);
	common->command.simple_commands[0]->command_count = arg_count;
	printf("arg_count is %d\n", common->command.simple_commands[0]->command_count);

//	common->command.simple_commands = ft_calloc(sizeof(t_simple_command *), 5);
//	common->command.simple_commands[0]->arguments = ft_calloc(sizeof(char *),arg_count + 1); // выделяем память для одного элемента
//	ft_init_struct(common, d);
//	common->command.simple_commands[0] = sc; //одна команда без пайпов
//	common->command.number_of_simple_commands++;

//	while (i < 7)
//	{
//		k = ft_test_shit(k);
//		i++;
//	}
//	printf("%d\n", k);

	line_to_arg(common, line);
	printf("<%s>\n", common->command.simple_commands[0]->arguments[0]);
	printf("<%s>\n", common->command.simple_commands[0]->arguments[1]);
	printf("<%s>\n", common->command.simple_commands[0]->arguments[2]);
	i = 0;
//	while(common->command.simple_commands[0]->arguments[i])
//	{
//		printf("<%s>\n", common->command.simple_commands[0]->arguments[i]);
//		i++;
//	}
//	while(i < 3)
//	{
//		printf("%s\n", common->command.simple_commands[0]->arguments[i]);
//		i++;
//	}
//	printf("%s", line);
	exit(0);
}