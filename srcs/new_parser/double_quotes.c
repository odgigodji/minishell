#include "minishell.h"

int ft_double_quotes(t_common *common, char *line)
{
	printf(RED"double_qoutes |%s|\n"RESET, line);
	int i;
	int len;
	int current_command;

	current_command = common->command.current_simple_command;
	i = 1;
//	while(line[i] && line[i] != '\'')
//	{
//		i++;
////		common->command.simple_commands[common->command.current_simple_command]->arg_count--;
//	}

//	ft_quotes_in_first_arg(common, line);
//common->command.simple_commands[common->command.current_simple_command]->arg_count = 4;
	len = ft_strlen_to_char(line + 1, '\"');
	printf(BLU"characters in qoutes %d\n"RESET, len);
//	ft_strlcpy(res, line + i, len + 1); 	//записываем все символы до спец символа во временную строку res
	i += do_arg(common, line, len, i); // создаем аргумент
//	printf("line after |%s|", line + i);
	return (i);
}