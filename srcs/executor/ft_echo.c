//
// Created by Mariam Scot on 2/18/21.
//

#include "minishell.h"

void	*ft_echo(void)
{
	char *line;

	while (get_next_line(0, &line))
	{
		puts(line);
		free(line);
	}
	return (NULL);
}

void	ft_cd(char *path)
{
	chdir(path);
}