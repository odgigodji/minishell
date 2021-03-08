//https://pubs.opengroup.org/onlinepubs/9699919799/utilities/cd.html#tag_20_14

/*
** Linux has a maximum filename length of 255 characters for most filesystems (including EXT4), and a maximum path of 4096 characters.
*/

#include "minishell.h"

void	mini_cd(char **simple_command, t_common *common)
{
	char	path[4096];
	char	home[4096];
	char	pwd[4096];

	if (simple_command[0][0] == '~')
	{
		ft_strlcpy(path, NULL, 4096);
	}
}