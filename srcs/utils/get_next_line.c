#include "minishell.h"

int	get_next_line(int fd, char **line)
{
	int		read_rv;
	char	buf;
	int		count;

	buf = '\0';
	if (NULL == (*line = malloc(10000)))
		return (0);
	**line = '\0';
	count = 0;
	while (1)
	{
		if (0 > (read_rv = read(fd, &buf, 1)))
			return (read_rv);
		if (buf != '\n' && read_rv != 0)
			(*line)[count++] = buf;
		else
		{
			(*line)[count] = '\0';
			return (read_rv);
		}
	}
}