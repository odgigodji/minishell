#include "minishell.h"

void	mini_exit(t_common *common)
{
	free_arg_list(&(common->env_variables_list));
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(0);
}