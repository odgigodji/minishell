#include <__wctype.h>

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>

# include "libft.h"

int		get_next_line(int fd, char **line);

void	pre_executer(int argc, char **argv, char **envp);

#endif