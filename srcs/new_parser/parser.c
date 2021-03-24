#include <stdio.h>
#include "minishell.h"

void ft_error(void)
{
	;
}

void ft_print_common(t_common *common)
{
	int i = 0;
	int j;
	while(common->command.simple_commands[i])
	{
		j = 0;
		printf(RED"arg_count: %d\n"RESET, common->command.simple_commands[i]->arg_count);
		while(common->command.simple_commands[i]->arguments[j])
		{
			printf(BLU"simple_command[%d]: "RESET, i);
			printf(YEL"sc->arguments[%d]"RESET,j);
			printf(GRN"|%s|\n"RESET, common->command.simple_commands[i]->arguments[j]);
			j++;
		}
		if (common->command.simple_commands[i]->arguments[j] == NULL)
		{
			printf(BLU"simple_command[%d]: "RESET, i);
			printf(YEL"sc->arguments[%d]"RESET,j);
			printf(GRN"|null|\n");
		}
		if ((i + 1) != common->command.number_of_simple_commands)
		printf("--next_simple_command--\n"RESET);
		i++;
	}
	if (common->command.simple_commands[i] == NULL)
		printf(BLU"simple_commands[%d]: (null)\n"RESET, i );
	i = 0;
	j = 0;
//	while(common->command.simple_commands[i]->out_file)
//	{
//		while(common->command.simple_commands[0]->out_file[j])
//		{
//			printf(RED"sc[%d] outfile[%d] is |%s|\n"RESET, i, j, common->command.simple_commands[i]->out_file[j]);
//			j++;
//		}
//		i++;
//	}
	printf("sc[0] outfile[0] %s", common->command.simple_commands[0]->out_file[0]);
	printf("sc[0] outfile[0] %s", common->command.simple_commands[1]->out_file[1]);
}

int	ft_parser(t_common *common, char *line)
{
//	char	*line;
	int		ret;
//	t_simple_command *simple_command;

//	line = NULL;
//	ft_putstr_fd("\033[35mminishell$ \033[0m", 0);
//	gnl_rv = get_next_line(0, &line);
//	printf("0\n");
//	ft_lexer(line);

//	printf("%s\n", line);
//	pars(common, line);     //-----------------старыый парсер

// --------------добавить цикл для обработки точки c запятой--------------

	ret = new_pars(common, line); //--------------- новый парсер
//	printf("simple command and arguments:\n");

	ft_print_common(common);


//	while (1) ;

//	free(line);

//	printf("result:");
//	if (NULL == (simple_command = simple_command_init(ft_split(line, ' '), 1, 1)))
//		return (-1);
//	common->command.simple_commands = malloc(sizeof(t_simple_command *) * 5);
//	common->command.simple_commands[0] = simple_command;
//	common->command.number_of_simple_commands = 1; // максимум одна команда если есть пайпы

//printf(CYN"-----------------------------------------------------------end of parser----------------------------------------------------\n"RESET);
	return (ret);
}