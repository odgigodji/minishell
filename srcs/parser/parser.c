#include <stdio.h>
#include "../../includes/minishell.h"

int ft_lexer(char *line)
{
	return 0;
}

void ft_parser(void)
{
	char *line;
	get_next_line(1, &line);
	ft_lexer(line);
	printf("%s", line);
}