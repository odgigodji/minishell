#include <stdio.h>
#include "minishell.h"

int ft_lexer(char *line)
{
	int i;
	char *res;
	int j;

	i = 0;
	j = 0;
	printf("|%s|\n", line);
//	while(line[i] != '\n')
//	{
//		if (line[i] == ' ')
//			i++;
////		if (line[i] == )
//	}
	return (1);
}

void ft_error(void)
{
	;
}

int	ft_parser(t_common *common)
{
	char	*line;
	int		gnl_rv;
	t_simple_command *simple_command;

	ft_putstr_fd("\033[35mminishell$ \033[0m", 0);
	gnl_rv = get_next_line(0, &line);
//	ft_lexer(line);
	if (!ft_strncmp(line, "exit", 4))
		return (0);
	if (NULL == (simple_command = simple_command_init(ft_split(line, ' '), 1, 1)))
		return (-1);
	common->command.simple_commands_struct = malloc(sizeof(t_simple_command *) * 5);
	common->command.simple_commands_struct[0] = simple_command;
	return (gnl_rv);
}