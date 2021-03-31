#include "minishell.h"

int ft_print_env(t_common *common, char **env_variables, char ***env_variables_list, char *res)
{
	int i = 0;
	int j = 0;
	int current_argument;

	current_argument = common->command.simple_commands[common->command.current_simple_command]->current_arg;
	char *ret = ft_calloc(sizeof(char), 100);
//	while(env_variables_list[i])
//	{
//		while(env_variables_list[i][j])
//		{
//			if (DEB_DOLLAR)
//				printf(YEL"|%s|\n"RESET, env_variables_list[i][j]);
//			j++;
//		}
//		i++;
//	}
	if (!(ret = get_envp_var_pointer(common, res)))
	{
		ft_do_arg_and_switch_to_next_arg(common, "\b", 1); //fixme
		return(ft_strlen(res));
	}
	if (DEB_DOLLAR	)
		printf(YEL"ret |%s|\n"RESET, ret);
	common->command.simple_commands[common->command.current_simple_command]->arguments[current_argument] = ft_calloc(sizeof(char)\
	, ft_strlen(ret) + 1);
	ft_do_arg_and_switch_to_next_arg(common, ret, ft_strlen(ret));
//	printf(RED"|%s|\n"RESET, ret);
	if (DEB_DOLLAR	)
	{
		printf(RED"!|%s|\n"RESET,common->command.simple_commands\
		[common->command.current_simple_command]->arguments[current_argument]);
		printf("%d\n", (int) ft_strlen(ret));
	}
	return (ft_strlen(res));
}


int ft_do_dollar1(t_common *common, char *line)
{
	int ret;
	char len;
	char res[50];
	int i = 0;

	if (DEB_DOLLAR	)
		printf(GRN"|%s|\n"RESET, line + 1);

	len = ft_strlen_to_char(line + 1, ' '); // len for ' ' fixme len for $

	if (DEB_DOLLAR	)
		printf("[%d]\n", len);
	//---------------for second $:

	ft_strlcpy(res, line + 1, len + 1);
	ret = ft_print_env(common, common->env_variables, common->env_variables_list, res);

	return (ret);
}

int ft_do_dollar(t_common *common, char *line)
{
	int ret;
	char len;
	char res[50];
	int i = 1;
	int j = 0;

	if (DEB_DOLLAR	)
		printf(GRN"after dollar:|%s|\n"RESET, line + 1);
	while(line[i] != ' ' && line[i])
	{
		while(line[i] != '$')
		{
			res[j] = line[i];
			j++;
			i++;
		}
	}
	printf(RED"|%s|\n"RESET, res);
	return (ft_strlen_to_char(line, ' '));
}
