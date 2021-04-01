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
	printf("var_name: |%s|\n", result);
	return (count);
}

//char	*get_envp_var_pointer(t_common *common, char *var)

//char		*expand_braces(char *token, t_common *common)
//{
//
//}

char		*expand_braces(char *token, t_common *common)
{
	int		count_token;
	int		count_result;
	char	*result;
	char	brace_flag;
	char	*env_variable = NULL;
	int		temp = 0;

	if (NULL == (result = malloc(sizeof(char) * MAX_PATH)))
		return (NULL);
	result[0] = '\0';
	brace_flag = '\0';
	count_token = 0;
	count_result = 0;
		puts(&token[count_token]);
	while (token[count_token])
	{
		if (token[count_token] == '"' || token[count_token] == '\'')
			if (token[count_token] == brace_flag || brace_flag == '\0')
			{
				puts("toggle");

				brace_flag = toggle_brace_flag(token[count_token], brace_flag);
				count_token++;
			}
		if (token[count_token] && '\'' == brace_flag)
		{
			puts("brace '");

			result[count_result] = token[count_token];
			count_token++;
			count_result++;
			result[count_result] = '\0';
		}
		else if (token[count_token] && '"' == brace_flag)
		{
			puts("brace \"");
			printf("<%d> (%s)\n", count_token, &token[count_token]);
			if (token[count_token] == '$')
			{
				temp += get_env_variable_name(&token[count_token], &env_variable);
				count_token += temp + 1;
				if (env_variable)
					count_result = strlcat(result, get_envp_var_pointer(common, env_variable), MAX_PATH);
				continue ;
			}
			result[count_result] = token[count_token];
			count_token++;
			count_result++;
			result[count_result] = '\0';
		}
		else if (token[count_token])
		{
			putchar(brace_flag);
			puts("else ");
			result[count_result] = token[count_token];
			count_token++;
			count_result++;
			result[count_result] = '\0';
		}
	}
	free(token);
	return (result);
}

char		**braces_expander(char **lexer_result, t_common *common)
{
	int	count;

	count = 0;
	while (lexer_result[count])
	{
		if (is_has_braces(lexer_result[count]))
			lexer_result[count] = expand_braces(lexer_result[count], common);
		count++;
	}
	return (lexer_result);
}

//t_command	*parser_m(char **tokens, )
//{
//
//}