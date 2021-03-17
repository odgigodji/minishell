#include "minishell.h"

int do_arg(t_common *common, char *line, int len_for_calloc, int increment)
{
	char *res;
	int i;
	t_simple_command sc;

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
	sc.arguments[0] = res;
//	printf("%s\n", sc.arguments[0]);
//	common->command.simple_commands[0]->arguments[0] = res;
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
	printf("|%s|\n", line + i);
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
//	while(!ft_strchr(spec, line[i]))
//	{
//		printf("%c", line[i]);
//		i++;
//	}
	len = len_for_calloc(line, common, i, spec);
	do_arg(common, line, len, i);
	i += len;
	printf("len_for_calloc is %d\n", len);
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

int arg_counter(char *line)														//fixme func
{
	return 5;
}

void ft_init_struct(t_common *common, int arg_count)
{
	common->command.simple_commands[0]->arguments = ft_calloc(sizeof(char *),arg_count + 1);
//	common->command = malloc(sizeof(t_command) * 1);
	;
}

void new_pars(t_common *common, char *line)
{
	char **arg;
	int i;
	static int k = 0; // number of argument

	i = 0;
//	int d = arg_counter(line);													//fixme написать функцию счетчика аргументов
//	common->command.simple_commands = malloc(sizeof(t_simple_command *) * 5);
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
//	while(i < 3)
//	{
//		printf("%s\n", common->command.simple_commands[0]->arguments[i]);
//		i++;
//	}
//	printf("%s", line);
	exit(0);
}