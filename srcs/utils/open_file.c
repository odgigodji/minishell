#include "minishell.h"

int	simple_command_open_file(char *file, int is_read, int is_cat)
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
		printf("%s: %s: No such file or directory\n", SHELL_NAME, file);
		return (-1);
	}
	return (fd);
}

int	open_file(t_pipe *pipe_variables, char *file_name, int is_read, int is_cat)
{
	int	fd;

	fd = simple_command_open_file(file_name, is_read, is_cat);
	if (-1 == fd)
		return (fd);
	if (is_read)
		pipe_variables->fdin = fd;
	else
		pipe_variables->fdout = fd;
	return (fd);
}

int	open_not_file(t_pipe *pipe_variables, int is_read)
{
	if (is_read)
	{
		pipe_variables->fdin = dup(pipe_variables->fdpipe[0]);
		return (pipe_variables->fdin);
	}
	else
	{
		pipe_variables->fdout = dup(pipe_variables->fdpipe[1]);
		return (pipe_variables->fdout);
	}
}

int	simple_command_in_out_fd(
			char **files_list,
			t_pipe *pipe_variables,
			int is_read,
			int is_cat)
{
	int	count;
	int	fd;

	count = 0;
	if (NULL != files_list && NULL != files_list[0])
	{
		while (files_list[count])
		{
			fd = open_file(pipe_variables, files_list[count], is_read, is_cat);
			count++;
			if (NULL != files_list[count])
				close(fd);
		}
		return (fd);
	}
	else
	{
		return (open_not_file(pipe_variables, is_read));
	}
}
