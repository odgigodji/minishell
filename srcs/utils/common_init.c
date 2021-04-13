#include "minishell.h"

t_common	*common_init(char **envp)
{
	t_common	*common;

	common = malloc(sizeof(t_common));
	common->env_variables_list = get_envp(envp);
	common->env_variables = envp;
	common->termcap = t_termcap_init();
	return (common);
}
