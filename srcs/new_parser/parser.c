#include <stdio.h>
#include "minishell.h"

void ft_error(void)
{
	;
}

int	ft_parser(t_common *common)
{
	char	*line;
	int		gnl_rv;
	int j;
//	t_simple_command *simple_command;

	line = NULL;
	ft_putstr_fd("\033[35mminishell$ \033[0m", 0);
	gnl_rv = get_next_line(0, &line);
//	printf("0\n");
//	ft_lexer(line);

//	printf("%s\n", line);
//	pars(common, line);     //-----------------старыый парсер

// --------------добавить цикл для обработки точки c запятой--------------

	new_pars(common, line); //--------------- новый парсер
	printf("simple command and arguments:\n");
	int i = 0;
	while(common->command.simple_commands[i])
	{
		j = 0;
		printf(RED"arg_count: %d\n"RESET, common->command.simple_commands[i]->arg_count);
		while(common->command.simple_commands[i]->arguments[j])
		{
			printf(BLU"simple_command[%d]: "RESET, i);
			printf(YEL"sc->arguments[%d]"RESET,j);
			printf(GRN"|%s|\n", common->command.simple_commands[i]->arguments[j]);
			j++;
		}
		if (common->command.simple_commands[i]->arguments[j] == NULL)
		{
			printf(BLU"simple_command[%d]: "RESET, i);
			printf(YEL"sc->arguments[%d]"RESET,j);
			printf(GRN"|null|\n");
		}
		printf("--next_simple_command--\n");
		i++;
	}

//	while (1) ;

	free(line);
//	printf("result:");
//	if (NULL == (simple_command = simple_command_init(ft_split(line, ' '), 1, 1)))
//		return (-1);
//	common->command.simple_commands = malloc(sizeof(t_simple_command *) * 5);
//	common->command.simple_commands[0] = simple_command;
//	common->command.number_of_simple_commands = 1; // максимум одна команда если есть пайпы
printf(CYN"-----------------------------------------------------------end of parser----------------------------------------------------\n"RESET);
	return (gnl_rv);
}