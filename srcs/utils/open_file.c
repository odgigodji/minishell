#include "minishell.h"

int		simple_command_open_file(char *file, int is_read, int is_cat)
{
	int	fd;

	if (is_read)
		fd = open(file, O_RDONLY);
	else
	{
		if (is_cat)
			fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
		else
			fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	}
	if (-1 == fd)
	{
		printf("%s: %s: No such file or directory", SHELL_NAME, file);
		return (-1);
	}
	return (fd);
}

int		simple_command_in_out_fd(char **files_list, t_pipe *pipe_variables, int is_read, int is_cat)
{
	int count;
	int	fd;

	count = 0;
	if (NULL != files_list[0])
	{
		while (files_list[count])
		{
			if (-1 == (fd = simple_command_open_file(files_list[count], is_read, is_cat)))
			{
				return (1);
			}
			pipe_variables->fdin = fd;
			count++;
			if (NULL != files_list[count])
				close(fd);
		}
		return (0);
	}
	else
	{
		pipe_variables->fdin = dup(pipe_variables->tmpin);
		return (0);
	}
}