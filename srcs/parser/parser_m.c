//
// Created by Mariam Scot on 4/1/21.
//

#include "minishell.h"

int			is_has_braces(char *token)
{
	int	count;

	count = 0;
	while (token && token[count])
	{
		if (token[count] == '\'' || token[count] == '"')
			return (1);
		count++;

	}
	return (0);
}

char 		toggle_brace_flag(char current_char, char brace_flag)
{
	if (current_char == brace_flag)
		return ('\0');
	else
		return (current_char);
}

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
//	printf("var_name: |%s|\n", result);
	return (count);
}

//char	*get_envp_var_pointer(t_common *common, char *var)

//char		*expand_braces(char *token, t_common *common)
//{
//
//}

int			expand_variable(char *token, t_common *common, char **result, int *count_result)
{
	int		count_token;
	char	*temp;

	if (token[1] == '?')
	{
		temp = ft_itoa(errno);
		strlcat(*result, get_envp_var_pointer(common, temp), MAX_PATH);
		count_token = 1 + (int)strlen(temp);
	}
	else
	{
		count_token = 1 + get_env_variable_name(token, &temp);    // + 1 на знак доллара
//		puts(token);
//		puts(temp);
		if (temp && get_envp_var_pointer(common, temp))
			strlcat(*result, get_envp_var_pointer(common, temp), MAX_PATH);
	}
	*count_result = (int) strlen(*result);
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

	token_p = token + 1;
	count = 0;
	count_temp = 0;
	temp = calloc(MAX_PATH, sizeof(char));
	while (token_p[count] && token_p[count] != '"')
	{
		if (token_p[count] == '$')
			count += expand_variable(&token[count + 1], common, &temp, &count_temp);
		else
		{
			if (token_p[count] == '"')
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
	char	*result;

	count_token = 0;
	count_result = 0;
	if (NULL == (result = calloc(sizeof(char), MAX_PATH)))
		return (NULL);
	while (token[count_token])
	{
		if (token[count_token] == '$')
			count_token += expand_variable(&token[count_token], common, &result, &count_result);
		else if (token[count_token] == '\'')
			count_token += expand_single_quotes(&token[count_token], common, &result, &count_result);
		else if (token[count_token] == '"')
			count_token += expand_double_quotes(&token[count_token], common, &result, &count_result);
		else
		{
			result[count_result] = token[count_token];
			count_token++;
			count_result++;
		}
	}
	return (result);
}

//char		*expand_braces(char *token, t_common *common)
//{
//	int		count_token;
//	int		count_result;
//	char	*result;
//	char	brace_flag;
//	char	*env_variable = NULL;
//	int		temp = 0;
//
//	if (NULL == (result = malloc(sizeof(char) * MAX_PATH)))
//		return (NULL);
//	result[0] = '\0';
//	brace_flag = '\0';
//	count_token = 0;
//	count_result = 0;
//	while (token[count_token])
//	{
//		if (token[count_token] == '"' || token[count_token] == '\'')
//			if (token[count_token] == brace_flag || brace_flag == '\0')
//			{
//				brace_flag = toggle_brace_flag(token[count_token], brace_flag);
//				count_token++;
//			}
//		if (token[count_token] && '\'' == brace_flag)
//		{
//			result[count_result] = token[count_token];
//			count_token++;
//			count_result++;
//			result[count_result] = '\0';
//		}
//		else if (token[count_token] && '\'' != brace_flag)	// else if (token[count_token] && '"' == brace_flag)
//		{
//			if (token[count_token] == '$')
//			{
//				count_token += get_env_variable_name(&token[count_token], &env_variable);
//				if (env_variable && get_envp_var_pointer(common, env_variable))
//					count_result = strlcat(result, get_envp_var_pointer(common, env_variable), MAX_PATH);
//				continue ;
//			}
//			result[count_result] = token[count_token];
//			count_token++;
//			count_result++;
//			result[count_result] = '\0';
//		}
//		else if (token[count_token] && token[count_token] != '"' && token[count_token] != '\'')
//		{
//			result[count_result] = token[count_token];
//			count_token++;
//			count_result++;
//			result[count_result] = '\0';
//		}
//	}
//	free(token);
//	return (result);
//}

char		**braces_expander(char **lexer_result, t_common *common)
{
	int	count;

	count = 0;
	while (lexer_result[count])
	{
//		if (is_has_braces(lexer_result[count]))
		lexer_result[count] = expand_braces(lexer_result[count], common);
		count++;
	}
	return (lexer_result);
}

//t_command	*parser_m(char **tokens, )
//{
//
//}