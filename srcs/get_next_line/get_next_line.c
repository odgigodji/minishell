/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namerei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:57:47 by namerei           #+#    #+#             */
/*   Updated: 2021/01/18 14:33:26 by namerei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
# include "minishell.h"

#define MAG   "\x1B[35m" //violet
#define RESET "\x1B[0m"

/*
** get_next_line function:
** # 1 parameter: file descriptor to read
** # 2 parameter: Value of what was read
** Return value
**  1: the string was read
**  0: EOF has been reached
** -1: an error occurred
*/

void			check_rem(char **rem, char **line, int bytes)
{
	char		*p_n;

	if (bytes == -1)
		return ;
	if (*rem)
	{
		p_n = ft_strchr(*rem, '\n');
		if (p_n)
		{
			*p_n = '\0';
			*line = ft_strdup(*rem);
			*rem = p_n + 1;
		}
		else
		{
			*line = ft_strdup(*rem);
			*rem = NULL;
		}
	}
	else
	{
		*line = ft_calloc(1, 1);
	}
}

void	prompt_q(void)
{
	ft_putstr_fd(MAG SHELL_NAME "$ " RESET, STDIN_FILENO);
}

static int		ret_res(int bytes_was_read, char *line)
{
	if (line == NULL)
		return (-1);
	else
		return ((bytes_was_read > 0) ? 1 : bytes_was_read);
}

int				get_next_line(int fd, char **line)
{
	static char buf[BUFFER_SIZE + 1];
	static char *rem = NULL;
	int			bytes_was_read;

	bytes_was_read = (BUFFER_SIZE < 1 || !line) ? (-1) : 1;
	check_rem(&rem, line, bytes_was_read);
	if (!rem && bytes_was_read == 1)
	{
		while (1)
		{
//			printf(RED"ggg\n"RESET);
			prompt_q();
			if ((bytes_was_read = read(fd, buf, BUFFER_SIZE)) <= 0)
				break;
			buf[bytes_was_read] = '\0';
			if ((rem = ft_strchr(buf, '\n')))
			{
				*rem = '\0';
				*line = ft_strjoin_with_free(*line, buf);
				if (!*(++rem))
					rem = NULL;
				break ;
			}
			*line = ft_strjoin_with_free(*line, buf);
		}
	}
//	printf(RED"ggg\n"RESET);
	return (ret_res(bytes_was_read, *line));
}
