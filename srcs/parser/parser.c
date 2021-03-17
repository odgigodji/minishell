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
	t_simple_command *simple_command;

	line = NULL;
	ft_putstr_fd("\033[35mminishell$ \033[0m", 0);

	gnl_rv = get_next_line(0, &line);
//	printf("0\n");
//	ft_lexer(line);

//	printf("%s\n", line);
//	pars(common, line);
	new_pars(common, line);
	printf("arguments:\n");
	int i =0;
	while(common->command.simple_commands[0]->arguments[i])
	{
		printf("%d argument is |%s|\n", i, common->command.simple_commands[0]->arguments[i]);
		i++;
	}
	if (common->command.simple_commands[0]->arguments[i] == NULL)
		printf("%d argument is |null|\n", i);
//	while (1) ;

	free(line);
//	printf("result:");
//	if (NULL == (simple_command = simple_command_init(ft_split(line, ' '), 1, 1)))
//		return (-1);
//	common->command.simple_commands = malloc(sizeof(t_simple_command *) * 5);
//	common->command.simple_commands[0] = simple_command;
//	common->command.number_of_simple_commands = 1; // максимум одна команда если есть пайпы
	return (gnl_rv);
}