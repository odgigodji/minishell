#include "minishell.h"

int	t_get_next_line(char **line, t_termcap *termcap)
{
	char		buffer[MAX_PATH];
	int			read_rv;
	int			input_rv;
	static int	count;

	buffer[0] = '\0';
	*line[0] = '\0';
	if (-1 == t_termcap_pre(termcap))
		return (-1);
	while (0 != ft_strncmp(buffer, "\4", 1))
	{
		read_rv = read(0, buffer, MAX_PATH);
		if (-1 == read_rv)
			return (-1);
		buffer[read_rv] = '\0';
		if (is_key(buffer))
			t_key_handle(buffer, termcap, line);
		else
		{
			input_rv = t_termcap_input_handle(buffer, termcap, line, read_rv);
			if (0 <= input_rv)
				return (input_rv);
		}
	}
	return (read_rv);
}
