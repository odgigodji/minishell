/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mscot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 13:38:02 by mscot             #+#    #+#             */
/*   Updated: 2021/04/14 13:38:05 by mscot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		free(old_pwd);
	else if (-1 == chdir(new_pwd))
	{
		g_errno = ENOENT;
		printf(RED "cd: no such file or directory: %s\n" RESET, new_pwd);
		free(old_pwd);
		free(new_pwd);
	}
	else
	{
		update_envp_var(common, "OLDPWD", old_pwd, 0);
		update_envp_var(common, "PWD", new_pwd, 0);
		free(old_pwd);
		free(new_pwd);
		g_errno = 0;
	}
}
