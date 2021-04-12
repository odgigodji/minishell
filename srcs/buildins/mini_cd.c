//https://pubs.opengroup.org/onlinepubs/9699919799/utilities/cd.html#tag_20_14

/*
** Linux has a maximum filename length of 255 characters for most filesystems (including EXT4), and a maximum path of 4096 characters.
*/

#include "minishell.h"

char	*mini_cd_get_new_pwd(char **simple_command, t_common *common)
{
	char	*new_pwd;

	new_pwd = NULL;
	if (simple_command[1] == NULL || simple_command[1][0] == '\0')
	{
		if (get_envp_var_pointer(common, "HOME"))
			new_pwd = ft_strdup(get_envp_var_pointer(common, "HOME"));
		else
			printf("%s: cd: HOME not set\n", SHELL_NAME);
	}
	else if (!ft_strncmp(simple_command[1], "-", 2))
	{
		if (get_envp_var_pointer(common, "OLDPWD"))
		{
			new_pwd = ft_strdup(get_envp_var_pointer(common, "OLDPWD"));
			printf("%s\n", new_pwd);
		}
		else
			printf("%s: cd: OLDPWD not set\n", SHELL_NAME);
	}
	else
		new_pwd = ft_strdup(simple_command[1]);
	return (new_pwd);
}

void	mini_cd(char **simple_command, t_common *common)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = getcwd(NULL, MAX_PATH);
	new_pwd = mini_cd_get_new_pwd(simple_command, common);
	if (NULL == new_pwd)
	{
		free(old_pwd);
		return ;
	}
	if (-1 == chdir(new_pwd))
	{
		errno = ENOENT;
		printf(RED "cd: no such file or directory: %s\n" RESET, new_pwd);
		free(old_pwd);
		free(new_pwd);
		return;
	}
	else
	{
		update_envp_var(common, "OLDPWD", old_pwd, 0);
		update_envp_var(common, "PWD", new_pwd, 0);
		free(old_pwd);
		free(new_pwd);
	}
}

//void	mini_cd_previous(t_common *common)
//{
//	char	*old_pwd;
//	char	*new_pwd;
//
//	if (-1 != get_envp_var_index(common, "OLDPWD")
//		&& NULL != common->env_variables_list[get_envp_var_index(common, "OLDPWD")][1])
//	{
//		if (-1 == chdir(common->env_variables_list[get_envp_var_index(common, "OLDPWD")][1]))
//		{
//			strerror((errno = ENOENT));
//			return;
//		}
//		old_pwd = ft_strdup(common->env_variables_list[get_envp_var_index(common, "OLDPWD")][1]);
//		update_envp_var(common, "OLDPWD", common->env_variables_list[get_envp_var_index(common, "PWD")][1], 0);
//		update_envp_var(common, "PWD", old_pwd, 0);
//		free(old_pwd);
//		ft_putstr_fd(common->env_variables_list[get_envp_var_index(common, "PWD")][1], 1);
//		ft_putstr_fd("\n", 1);
//	}
//	else
//	{
//		printf("minishell: cd: OLDPWD not set\n");
//		errno = 1;
//	}
//}

//void	mini_cd(char **simple_command, t_common *common)
//{
//	char	*old_pwd;
//	char	*new_pwd;
//
//	if (NULL == simple_command[1] || '\0' == simple_command[1][0] || ft_strncmp(simple_command[1], "-", 2))
//	{
//		old_pwd = getcwd(NULL, MAX_PATH);
//		if (NULL == (new_pwd = malloc(sizeof(char) * MAX_PATH)))
//			return;
//		if (NULL == simple_command[1] || '\0' == simple_command[1][0])
//		{
//			if (NULL == (get_envp_var_pointer(common, "HOME")))
//			{
//				printf("%s: cd: HOME not set\n", SHELL_NAME);
//				return;
//			}
//			ft_strlcpy(new_pwd, get_envp_var_pointer(common, "HOME"), MAX_PATH);
//		}
//		update_envp_var(common, "OLDPWD", old_pwd, 0);
//		if (NULL == simple_command[1] || '\0' == simple_command[1][0])
//		{
//			if (-1 == chdir(new_pwd))
//			{
//				errno = ENOENT;
//				printf("cd: no such file or directory: %s\n", new_pwd);
//				free(new_pwd);
//				return;
//			}
//		}
//		else
//		{
//			if (-1 == chdir(simple_command[1]))
//			{
//				errno = ENOENT;
//				printf("cd: no such file or directory: %s\n", simple_command[1]);
//				return;
//			}
//		}
//		new_pwd = getcwd(NULL, MAX_PATH);
//		if (NULL == new_pwd)
//			return;
//		update_envp_var(common, "PWD", new_pwd, 0);
//		free(new_pwd);
//	}
//	else // "cd -"
//	{
//		mini_cd_previous(common);
//	}
//}
