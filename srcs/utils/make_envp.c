#include "minishell.h"

char	*make_arg_line(char **arg_array_line)
{
	size_t	line_len;
	char	*result;

	if (NULL == arg_array_line)
		return (NULL);
	if (arg_array_line[1])
		line_len = ft_strlen(
				arg_array_line[0]) + ft_strlen(arg_array_line[1]) + 2;
	else
		line_len = ft_strlen(arg_array_line[0]) + 1;
	result = malloc(sizeof(char) * line_len);
	result[0] = '\0';
	ft_strlcat(result, arg_array_line[0], line_len);
	if (NULL != arg_array_line[1])
	{
		ft_strlcat(result, "=", line_len);
		ft_strlcat(result, arg_array_line[1], line_len);
	}
	return (result);
}

char	**make_envp(t_common *common)
{
	int		list_len;
	char	**envp;
	int		count;

	list_len = args_list_len(common->env_variables_list);
	envp = malloc(sizeof(char *) * (list_len + 1));
	count = 0;
	while (common->env_variables_list[count])
	{
		envp[count] = make_arg_line(common->env_variables_list[count]);
		count++;
	}
	envp[count] = NULL;
	common->env_variables = envp;
	return (envp);
}
