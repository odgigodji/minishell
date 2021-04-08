//
// Created by Mariam Scot on 4/1/21.
//

#include "minishell.h"

int			get_env_variable_name(char *line, char **variable_name)
{
	int 	count;
	char	*line_p;
	char	*result;

	count = 0;
	if (line == NULL)
	{
		printf("smth points to NULL in get_env_variable_name\n");
		return (-1);
	}
	line_p = line + 1;
	if (NULL == (result = malloc(sizeof(char) * MAX_NAME)))
		return (-1);
	while (line_p[count] && (ft_isalnum(line_p[count]) || line_p[count] == '_'))
	{
		result[count] = line_p[count];
		count++;
	}
	result[count] = '\0';
	*variable_name = result;
	return (count);
}

int			expand_variable(char *token, t_common *common, char **result, int *count_result)
{
	int		count_token;
	char	*temp;

	if (token[1] == '?')
	{
		temp = ft_itoa(errno);
		strlcat(*result, temp, MAX_PATH);
		count_token = 1 + (int)ft_strlen(temp);
	}
	else if (token[1] == '$')
	{
		temp = ft_itoa(getpid());
		strlcat(*result, temp, MAX_PATH);
		count_token = 2;
	}
	else if (token[0] == '~' && token[1] == '\0')
	{
		strlcat(*result, get_envp_var_pointer(common, "HOME"), MAX_PATH);
		count_token = 1;
	}
	else
	{
		count_token = 1 + get_env_variable_name(token, &temp);    // + 1 на знак доллара
		if (temp && get_envp_var_pointer(common, temp))
			strlcat(*result, get_envp_var_pointer(common, temp), MAX_PATH);
	}
	*count_result = (int)ft_strlen(*result);
	return (count_token);
}

int			expand_single_quotes(char *token, t_common *common, char **result, int *count_result)
{
	char	*token_p;
	int		count;
	char	temp[MAX_PATH];

	token_p = token + 1;
	count = 0;
	temp[0] = '\0';
	while (token_p[count] && token_p[count] != '\'')
	{
		temp[count] = token_p[count];
		count++;
	}
	temp[count] = '\0';
	if (temp[0])
		strlcat(*result, temp, MAX_PATH);
	return (count + 1);
}

int			expand_double_quotes(char *token, t_common *common, char **result, int *count_result)
{
	char	*token_p;
	int		count;
	int		count_temp;
	char	*temp;
	int		flag_back_slash;

	token_p = token + 1;
	count = 0;
	count_temp = 0;
	temp = calloc(MAX_PATH, sizeof(char));
	flag_back_slash = 0;
	while (token_p[count] && !(token_p[count] == '"'))
	{
		if (token_p[count] == '\\')
		{
			flag_back_slash = toggle_back_slash_flag(flag_back_slash, &token_p[count], count);
			if (flag_back_slash % 2 != 0)
				count++;
		}
		if (token_p[count] == '$' && token_p[count - 1] != '\\')
			count += expand_variable(&token[count + 1], common, &temp, &count_temp);
		else
		{
			if (token_p[count] == '"' && flag_back_slash % 2 == 0) //token_p[count - 1] != '\\'
				break ;
			temp[count_temp] = token_p[count];
			count++;
			count_temp++;
		}
	}
	temp[count_temp] = '\0';
	if (temp[0])
		strlcat(*result, temp, MAX_PATH);
	return (count + 2);
}

char		*expand_braces(char *token, t_common *common)
{
	int		count_token;
	int		count_result;
	int		flag_back_slash;
	char	*result;
	char	temp;

	count_token = 0;
	count_result = 0;
	flag_back_slash = 0;
	if (NULL == (result = calloc(sizeof(char), MAX_PATH)))
		return (NULL);
	temp = '\0';
	while (token[count_token])
	{
		temp = token[count_token];
		if (token[count_token] && token[count_token] == '\\')
		{
			flag_back_slash = toggle_back_slash_flag(flag_back_slash, &token[count_token], count_token);
//			if (flag_back_slash % 2 != 0)
//			{
//				flag_back_slash++;
//				count_token++;
//			}
		}
		if (token[count_token] == '$' && flag_back_slash % 2 == 0)
			count_token += expand_variable(&token[count_token], common, &result, &count_result);
		else if (token[count_token] == '\'' && flag_back_slash % 2 == 0)
			count_token += expand_single_quotes(&token[count_token], common, &result, &count_result);
		else if (token[count_token] == '"' && flag_back_slash % 2 == 0)
			count_token += expand_double_quotes(&token[count_token], common, &result, &count_result);
		else if (token[count_token])
		{
			result[count_result] = token[count_token];
			count_token++;
			count_result++;
		}
	}
	return (result);
}

char		**braces_expander(char **lexer_result, t_common *common)
{
	int	count;

	count = 0;
	while (lexer_result[count])
	{
		lexer_result[count] = expand_braces(lexer_result[count], common);
		count++;
	}
	return (lexer_result);
}
