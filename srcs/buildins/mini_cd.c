//https://pubs.opengroup.org/onlinepubs/9699919799/utilities/cd.html#tag_20_14

/*
** Linux has a maximum filename length of 255 characters for most filesystems (including EXT4), and a maximum path of 4096 characters.
*/

#include "minishell.h"

void	mini_cd(char **simple_command, t_common *common)
{
	char	path[MAX_PATH];

	path[0] = '\0';
	if (simple_command[0][0] == '~')
	{
		ft_strlcpy(path, get_envp_variable(common, "HOME"), MAX_PATH);
		ft_strlcat(path, "/", MAX_PATH);
		ft_strlcat(path, simple_command[1], MAX_PATH);
	}
	else if (simple_command[0][0] != '/')
	{
		ft_strlcpy(path, get_envp_variable(common, "PWD"), MAX_PATH);
		ft_strlcat(path, "/", MAX_PATH);
		ft_strlcat(path, simple_command[1], MAX_PATH);
	}
	else if (simple_command[0][0] != '.' && simple_command[0][1] != '.')
		return ;	// сделать переход в педыдущую папку
	else			// абсолютный путь
		ft_strlcat(path, simple_command[1], MAX_PATH);
	if (-1 == chdir(path))
		return ;	// fixme сделать ошибку

}