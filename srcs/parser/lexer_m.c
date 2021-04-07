//
// Created by Mariam Scot on 4/1/21.
//

#include "minishell.h"

int			is_spec_symbol(char c)
{
	int	count;

	count = 0;
	while (SPEC_SYMBOL[count])
	{
		if (SPEC_SYMBOL[count] == c)
			return (1);
		count++;
	}
	return (0);
}

/*
** функция которая бежит по строке и возвращается завалидированный токен
** По одному токену за один раз
*/

int			get_token(char *line, char **token)
{
	int		count_line;
	int		count_token;
	char	buffer[100];
	char	brace_flag;
	int		back_slash_flag;

	count_line = 0;
	count_token = 0;
	buffer[0] = '\0';
	back_slash_flag = 0;
	while (line[count_line] && !is_spec_symbol(line[count_line]))
	{
		// back slash
		if (line[count_line] == '"' || line[count_line] == '\'')
		{
			brace_flag = line[count_line];
			while (brace_flag)
			{
				buffer[count_token] = line[count_line];
				count_line++;
				count_token++;
				if (line[count_line] == brace_flag)
					brace_flag = 0;
			}
		}
		if (line[count_line] && line[count_line] != ' '
		&& (!is_spec_symbol(line[count_line])
			|| is_spec_symbol(line[count_line])))
		{
			buffer[count_token] = line[count_line];
			count_line++;
			count_token++;
		}
		else if (line[count_line] == ' ' || is_spec_symbol(line[count_line]))
		{
			break;
		}
		else
			count_line++;
	}
	buffer[count_token] = '\0';
	*token = strdup(buffer);
	return (count_line);
}

char		toggle_brace_flag_lexer(char flag, char current_char)
{
	if (flag == '\0')
		return (current_char);
	else if (current_char == flag)
		return ('\0');
	else
		return (flag);
}

int			toggle_back_slash_flag(int flag, char *line, int count)
{
	if (count == 0 || *(line - 1) != '\\')
		return (1);
	else
		return (flag + 1);
}

int			get_token2(char *line, char **token)
{
	int		count_line;
	int		count_token;
	char	buffer_token[MAX_PATH];
	char	flag_brace;
	int		flag_back_slash;

	count_line = 0;
	count_token = 0;
	flag_brace = 0;
	flag_back_slash = 0;
	buffer_token[0] = '\0';
	while (line[count_line])
	{
		if (line[count_line] == '"' || line[count_line] == '\'')
			flag_brace = toggle_brace_flag_lexer(flag_brace, line[count_line]);
		if ('\0' == flag_brace && (line[count_line] == ' ' || is_spec_symbol(line[count_line])) && flag_back_slash % 2 == 0)
			break ;
		if (line[count_line] == '\\')
			flag_back_slash = toggle_back_slash_flag(flag_back_slash, &line[count_line], count_line);

		buffer_token[count_token] = line[count_line];
		count_line++;
		count_token++;
	}
	buffer_token[count_token] = '\0';
	*token = strdup(buffer_token);
	return (count_line);
}

/*
 * 		if (line[count_line] == '\\' && !flag_brace)
		{
			flag_back_slash = toggle_back_slash_flag(flag_back_slash, &line[count_line], count_line);
			count_line++;
		}
		if (line[count_line] == '\'')
		{
			flag_brace = toggle_brace_flag_lexer(flag_brace, line[count_line]);
		}
 */

/*
 * 		$TERM""text => TERM
 * 		начинается с $
 */
char		*get_variable_name(char *line)
{
	char	*result;
	char	*line_p;
	int		count;

	count = 0;
	result = malloc(MAX_NAME * sizeof(char));
	if (line[0] != '$')
		return (NULL);
	line_p = line + 1; // смещаем на $
	while (line_p[count] && (line_p[count] == '_' || ft_isalnum(line_p[count])))
	{
		result[count] = line_p[count];
		count++;
	}
	result[count] = '\0';
	return (result);
}

//	var_value = char	*get_envp_var_pointer(t_common *common, char *var)
int			expand_variable_lexer(char *line, t_common *common, char **buffer_token, int *count_token)
{
	char	*var_name;
	char	*var_value;
	char	*line_p;
	int		count;

	if (line[1] == '?')
	{
		line_p = ft_itoa(errno);
		*count_token = strlcat(*buffer_token, line_p, MAX_PATH);
		count = ft_strlen(line_p);
		free(line_p);
		return (count + 1);
	}
	var_name = get_variable_name(line);							// отправляем с $
	var_value = get_envp_var_pointer(common, line + 1);		// + 1 смещаем на $
	line_p = line + 1;
	count = 0;
	if (var_value)
		*count_token = strlcat(*buffer_token, var_value, MAX_PATH);
	while (line_p[count] && (line_p[count] == '_' || ft_isalnum(line_p[count])))
		count++;
	return (count + 1);
}

int			get_token3(char *line, char **token, t_common *common)
{
	int		count_line;
	int		count_token;
	char	*buffer_token;
	char	flag_brace_single;
	char	flag_brace_double;
	char	flag_back_slash;
	char	temp;

	temp = 0;
	count_line = 0;
	count_token = 0;
	flag_brace_single = 0;
	flag_brace_double = 0;
	flag_back_slash = 0;
	buffer_token = calloc(MAX_PATH, sizeof(char));
	while (line[count_line])
	{
		temp = line[count_line];
		if (line[count_line] == '\\' && !flag_back_slash && !flag_brace_single && (ft_strchr("$\\\"", line[count_line + 1])))
		{
			flag_back_slash = 1;
			count_line++;
			continue ;
		}
		if (line[count_line] == '\'' && !flag_brace_double && !flag_back_slash)
		{
			flag_brace_single = !flag_brace_single;
			count_line++;
			continue ;
		}
		if (line[count_line] == '"' && !flag_brace_single && !flag_back_slash)
		{
			flag_brace_double = !flag_brace_double;
			count_line++;
			continue ;
		}
		if ('\0' == line[count_line] || ((line[count_line] == ' ' || is_spec_symbol(line[count_line]))
			&& !flag_back_slash && !flag_brace_single && !flag_brace_double))
		{
			break;
		}
		if (line[count_line] == '$' && !flag_brace_single && !flag_back_slash)
		{
			count_line += expand_variable(&line[count_line], common, &buffer_token, &count_token);
			continue ;
		}
		temp = line[count_line];
		buffer_token[count_token] = line[count_line];
		count_line++;
		count_token++;
		flag_back_slash = 0;
	}
	buffer_token[count_token] = '\0';
	*token = strdup(buffer_token);
	return (count_line);
}

char		*get_braced_token(char *line)
{
	int		count;
	char	*token;

	count = 0;
	if (NULL == (token = malloc(sizeof(char) * MAX_PATH)))
		return (NULL);
	token[count] = '\0';
	while (line[count])
	{
		token[count] = line[count];
		count++;
//		if (line[count] == ' ' && line[count - 1] != brace_type)
//		{
//			break ;
//		}
		if (((line[count] == '\'' || line[count] == '"') && line[count + 1] == ' ')
			|| line[count] == '\0')
		{
			token[count] = line[count];
			token[count + 1] = '\0';
			break ;
		}
	}
	return (token);
}

int			get_spec_token_length(char *line, char *token)
{
	if (line[0] == '|')
		return (1);
	else if (line[0] == '>')
	{
		if (line[1] != '>')
			return (1);
		else
			return (2);
	}
	else if (line[0] == '<')
	{
		if (line[1] != '<')
			return (1);
		else
			return (2);
	}
	else if (line[0] == '"' || line[0] == '\'')
		return ((int)strlen(token));
	return (0);
}

int			get_spec_token(char *line, char **token)
{
	char *a = SPEC_SYMBOL;

	if (line[0] == '|')
	{
		*token = strdup(PIPE);
	}
	else if (line[0] == '>')
	{
		if (line[1] != '>')
			*token = strdup(GREAT);
		else
			*token = strdup(GREATGREAT);
	}
	else if (line[0] == '<')
	{
		if (line[1] != '<')
			*token = strdup(LESS);
		else
			*token = strdup(GREATLESS);
	}
//	else if (line[0] == '\'' || line[0] == '"')
//		*token = get_braced_token(line);
	return (get_spec_token_length(line, *token));
}

char		**lexer(char *line, t_common *common)
{
	int		count;
	int		count_result;
	char	*token;
	char	**result;

	count = 0;
	count_result = 0;
	token = NULL;
	if (NULL == (result = malloc(sizeof(char *) * 100)))
		return (NULL);
	result[0] = NULL;
	while(line[count] && line[count] != ';')
	{
		if (!is_spec_symbol(line[count]))
			count += get_token3(&line[count], &token, common);
		else
			if (line[count] != ' ')
				count += get_spec_token(&line[count], &token);
		if (token && token[0] != '\0')
		{
			result[count_result] = token;
			count_result++;
			result[count_result] = NULL;
		}
		if (line[count] == ' ' && '\0' != line[count])
			count++;
	}
	return (result);
}
