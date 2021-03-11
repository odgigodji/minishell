#include "minishell.h"

//void	mini_pwd(char **envp)
//{
//	int		count;
//	char	*pwd;
//
//	count = 0;
//	while (envp[count] && ft_strncmp(envp[count], "PWD", 3))
//		count++;
//	pwd = ft_strrchr(envp[count], '=') + 1;
//	ft_putstr_fd(pwd, 1);
//	ft_putchar_fd('\n', 1);
//}

void	mini_pwd(t_common *common)
{
	int		count;

	count = 0;
	while (common->env_variables_list[count] && ft_strncmp(common->env_variables_list[count][0], "PWD", 3))
		count++;
	ft_putstr_fd(common->env_variables_list[count][1], 1);
	ft_putchar_fd('\n', 1);
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