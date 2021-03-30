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
	ret = get_envp_var_pointer(common, res);
	printf(YEL"ret |%s|\n"RESET, ret);
	common->command.simple_commands[common->command.current_simple_command]->arguments[current_argument] = ft_calloc(sizeof(char)\
	, ft_strlen(ret) + 1);
//	ft_strlcpy(common->command.simple_commands[common->command.current_simple_command]->arguments[current_argument], \
//	ret, ft_strlen(ret) + 1);
//	ft_strlcpy(res, line + 1, len + 1);
	ft_do_arg_and_switch_to_next_arg(common, ret, ft_strlen(ret));
//	printf(RED"|%s|\n"RESET, ret);
	printf(RED"!|%s|\n"RESET, common->command.simple_commands[common->command.current_simple_command]->arguments[current_argument]);
	printf("%d\n", (int)ft_strlen(ret));
	return (ft_strlen(res));
}


int ft_do_dollar(t_common *common, char *line)
{
	int ret;
	printf(GRN"|%s|\n"RESET, line + 1);
	char len;
	char res[50];

	len = ft_strlen_to_char(line + 1, ' ');
	printf("[%d]\n", len);
	ft_strlcpy(res, line + 1, len + 1);
//	ft_do_arg_and_switch_to_next_arg(common, res, len);
//	char res[10] = "SHELL";
	ret = ft_print_env(common, common->env_variables, common->env_variables_list, res);

	return (ret);
}
