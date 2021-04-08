#include "minishell.h"

int		env_list_length(t_common *common)
{
	int		count;
	char	***env_p;

	count = 0;
	env_p = common->env_variables_list;
	while (env_p[count])
		count++;
	return (count);
}

void	print_export_line(char **line)
{
	if (line[1])
		printf("declare -x %s=\"%s\"\n", line[0], line[1]);
	else
		printf("declare -x %s\n", line[0]);
}

int		get_next_export_index(char ***envp, int	current)
{
	int count;
	int count_2;
	int temp;

	count = 0;
	count_2 = 0;
	temp = current;
//	while (envp[count])
//	{
//		if (0 > ft_strncmp(envp[count][0], envp[current][0], ft_strlen(envp[current][0])))
//		{
//			count_2 = 0;
//			while (envp[count_2])
//			{
//				if (0 < ft_strncmp(envp[count_2][0], envp[count][0], ft_strlen(envp[count_2][0]))
//					&& 0 > ft_strncmp(envp[count][0], envp[current][0], ft_strlen(envp[current][0])))
//					temp = count;
//				count_2++;
//			}
//		}
//		count++;
//	}
//	return (temp);
	return (current);
}

void	print_export(t_common *common)
{
	int	count;
	int	next;

	count = 0;
	next = 0;
	while (common->env_variables_list[count])
	{
		next = get_next_export_index(common->env_variables_list, count);
		print_export_line(common->env_variables_list[next]);
		count++;
	}
}

int		is_append(char *arg)
{
	if (NULL == arg || NULL == ft_strchr(arg, '='))
		return (0);
	if (*(ft_strchr(arg, '=') - 1) == '+')
		return (1);
	else
		return (0);
}

int		is_key_valid(char *key)
{
	int	count;

	count = 0;
	while (key[count])
	{
		if (!(ft_isalnum(key[count]) || key[count] == '_'))
			return (0);
		count++;
	}
	return (1);
}

void	mini_export(t_common *common, char **simple_command)
{
	char	**key_value;
	int		count;

	count = 1;
	if (NULL == simple_command[1])
	{
		print_export(common);
	}
	else
	{
		while (simple_command[count])
		{
			key_value = get_key_and_value(simple_command[count]);
			if (!is_key_valid(key_value[0]))
			{
				printf("%s: export: %s not a valid identifier\n", SHELL_NAME, key_value[0]);
				continue ;
			}
			update_envp_var(common, key_value[0], key_value[1], is_append(simple_command[count]));
			free(key_value[0]);
			free(key_value[1]);
			count++;
		}
	}
}