#include "minishell.h"

void	free_line_list(char **split_list)
{
	int		count;

	count = 0;
	while (split_list[count] != NULL)
	{
		free(split_list[count]);
		count++;
	}
	free(split_list[count]);
	free(split_list);
}