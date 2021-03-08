#include "minishell.h"

void	mini_pwd(char **envp)
{
	int		count;
	char	*pwd;

	count = 0;
	while (envp[count] && ft_strncmp(envp[count], "PWD", 3))
		count++;
	pwd = ft_strrchr(envp[count], '=') + 1;
	ft_putstr_fd(pwd, 1);
}

char	*get_pwd(char **envp)
{
	int		count;
	char	*pwd;

	count = 0;
	while (envp[count] && ft_strncmp(envp[count], "PWD", 3))
		count++;
	pwd = ft_strrchr(envp[count], '=') + 1;
	return (pwd);
}