#include "minishell.h"

char	**split_path(t_common *common)
{
	char	link[MAX_PATH];
	char	*path_p;

	link[0] = '\0';
	path_p = get_envp_var_pointer(common, "PATH");
	if (path_p)
		return (ft_split(path_p, ':'));
	return (NULL);
}
