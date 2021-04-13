#include "minishell.h"

int	get_env_variable_name(char *line, char **variable_name)
{
	int		count;
	char	*line_p;
	char	*result;

	count = 0;
	if (line == NULL)
	{
		printf("smth points to NULL in get_env_variable_name\n");
		return (-1);
	}
	line_p = line + 1;
	result = malloc(sizeof(char) * MAX_NAME);
	if (NULL == result)
		return (-1);
	while (line_p[count]
		&& (ft_isalnum(line_p[count]) || line_p[count] == '_'))
	{
		result[count] = line_p[count];
		count++;
	}
	result[count] = '\0';
	*variable_name = result;
	return (count);
}

void	expand_variable_question(char **temp, char **result, int *count_token)
{
	*temp = ft_itoa(g_errno);
	strlcat(*result, (*temp), MAX_PATH);
	(*count_token) = 2;
	free(*temp);
}

int	expand_variable(char *token,
					  t_common *common,
					  char **result,
					  int *count_result)
{
	int		count_token;
	char	*temp;

	if (token[1] == '?')
		expand_variable_question(&temp, result, &count_token);
	else if (token[0] == '~')
	{
		if (get_envp_var_pointer(common, "HOME")
			&& (ft_strchr(" ", token[1]) || token[1] == '\0'))
			strlcat(*result, get_envp_var_pointer(common, "HOME"), MAX_PATH);
		else
			strlcat(*result, "~", MAX_PATH);
		count_token = 1;
	}
	else
	{
		count_token = 1 + get_env_variable_name(token, &temp);
		if (temp && get_envp_var_pointer(common, temp))
			strlcat(*result, get_envp_var_pointer(common, temp), MAX_PATH);
		free(temp);
	}
	*count_result = (int)ft_strlen(*result);
	return (count_token);
}
