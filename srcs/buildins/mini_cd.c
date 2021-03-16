//https://pubs.opengroup.org/onlinepubs/9699919799/utilities/cd.html#tag_20_14

/*
** Linux has a maximum filename length of 255 characters for most filesystems (including EXT4), and a maximum path of 4096 characters.
*/

#include "minishell.h"

void	mini_cd(char **simple_command, t_common *common)
{
	char	*old_pwd;
	char	*new_pwd;

	if (ft_strncmp(simple_command[1], "-", 2))
	{
		if (NULL == (old_pwd = malloc(sizeof(char) * MAX_PATH))
			|| NULL == (new_pwd = malloc(sizeof(char) * MAX_PATH))
			|| NULL == (getcwd(old_pwd, MAX_PATH)))
			return ;
		update_envp_var(common, "OLDPWD", old_pwd, 0);
		if (-1 == chdir(simple_command[1]))
			return ;
		if (NULL == (getcwd(new_pwd, MAX_PATH)))
			return ;
		update_envp_var(common, "PWD", new_pwd, 0);
	}
	else // "cd -"
	{
		old_pwd = common->env_variables_list[get_envp_var_index(common, "PWD")][1];
		common->env_variables_list[get_envp_var_index(common, "PWD")][1] =
				common->env_variables_list[get_envp_var_index(common, "OLDPWD")][1];
		common->env_variables_list[get_envp_var_index(common, "OLDPWD")][1] = old_pwd;
		ft_putstr_fd(common->env_variables_list[get_envp_var_index(common, "PWD")][1], 1);
		ft_putstr_fd("\n", 1);
		if (-1 == chdir(common->env_variables_list[get_envp_var_index(common, "PWD")][1]))
		{
			strerror((errno = ENOENT));
			return ;
		}
	}
}