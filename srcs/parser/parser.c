#include <stdio.h>
#include "../../includes/minishell.h"

int ft_lexer(char *line)
{
	return (0);
}

int	ft_parser(void)
{
	char *line;
	int		gnl_rv;

	ft_putstr_fd("\033[35mminishell$ \033[0m", 0);
	gnl_rv = get_next_line(1, &line);
	ft_lexer(line);
	if (!ft_strncmp(line, "exit", 4))
		return (0);
	return (gnl_rv);
}