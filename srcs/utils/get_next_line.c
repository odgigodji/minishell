#include "minishell.h"

int	get_next_line(int fd, char **line)
{
//	int ret = 1;
//	int i = 0;
//	char *str;
//	char c;
//
//	str = malloc(sizeof(char) * 10000);
//	if (str == NULL)
//		return (0);
//	while (i < 10000)
//		str[i++] = '\0';
//	i = 0;
//	while (ret > 0)
//	{
//		ret = read(0, &c, 1);
//		if (ret > 0 && c != '\n')
//			str[i++] = c;
//		if (ret > 0 && c == '\n')
//		{
//			*line = str;
//			return 1;
//		}
//	}
//	*line = str;
//	return 0;


	int		read_rv;
	char	buf;
	int		count;

	buf = '\0';
	if (NULL == (*line = ft_calloc(sizeof(char), 10000)))
		return (0);
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