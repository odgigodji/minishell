#include "minishell.h"

void ft_do_arg_and_switch_to_next_arg(t_common *common, char *res, int len_for_calloc)
{
//	printf("number_of_arg is %d\n", common->command.simple_commands[0]->arg_number);
//	printf("res is %s\n", res);
	common->command.simple_commands[0]->arguments[common->command.simple_commands[0]->arg_number] = ft_strdup(res);
//	printf(GRN"<%s>\n"RESET, common->command.simple_commands[0]->arguments[common->command.simple_commands[0]->arg_number]);
	if (common->command.simple_commands[0]->arg_number != common->command.simple_commands[0]->arg_count)
		common->command.simple_commands[0]->arg_number++;
}

int do_arg(t_common *common, char *line, int len_for_calloc, int increment)
{
//	char *res;
	int i;
	char res[len_for_calloc];
	i = 0;
	ft_strlcpy(res, line + increment, len_for_calloc);
//	printf("len for calloc is %d [%s]\n", len_for_calloc, line + increment);
//	printf("---%s---\n", res);
	ft_do_arg_and_switch_to_next_arg(common, res, len_for_calloc);
	return (increment + len_for_calloc);
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
	char spec[6] = " '|\"$\t";

	i = increment;
	len = len_for_calloc(line, common, i, spec); // для нулевого символа + 1
	do_arg(common, line, len + 1, i);
	i += len;
//	printf("len_for_calloc is %d\n", len);
	return (i);
}

void line_to_arg(t_common *common, char *line)
{
	int i;

	i = 0;
	printf("|%s|\n", line);
	while(line[i] && line[i] != ';')
	{
		if (line[i] == ' ' || line[i] == '"' || line[i] == '\'' || line[i] == '\t' \
		|| line[i] == '|' || line[i] == '$')
			;
		else
			i = make_args(line, common, i);
		i++;
	}
	common->command.simple_commands[0]->arguments[common->command.simple_commands[0]->arg_count] = NULL;
}

int	ft_arg_counter(char *s)																//fixme
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

void ft_init_struct(t_common *common, int arg_count)
{
//	common->command = ft_calloc(sizeof(t_simple_command), 1);
	common->command.simple_commands = ft_calloc(sizeof(t_simple_command *), 1); // пять команд это типо если будут пайпы
	common->command.simple_commands[0] = ft_calloc(sizeof(t_simple_command) , 1); //одна команда без пайпов
	common->command.simple_commands[0]->arguments = ft_calloc(sizeof(char *),arg_count + 1);
	common->command.simple_commands[0]->arg_number = 0;
	common->command.number_of_simple_commands = 1;
	common->command.current_simple_command = 0;
//	common->command.simple_commands[0]->arguments[arg_count] = NULL;
	;
}

void new_pars(t_common *common, char *line)
{
	printf("------используется новый парсер, чтобы вернуться на старый нужно закомитить new_pars в parser.c и раскомитьть pars---------\n");
	char **arg;
	int i;
	static int k = 0; // number of argument

	i = 0;

	int arg_count = ft_arg_counter(line);
	ft_init_struct(common, arg_count);														//fixme написать функцию счетчика аргументов
	printf(BLU"current simple command is %d\n"RESET, common->command.current_simple_command);
	common->command.simple_commands[0]->arg_count = arg_count;

	printf("arg_count is %d\n", common->command.simple_commands[0]->arg_count);

	line_to_arg(common, line);

}