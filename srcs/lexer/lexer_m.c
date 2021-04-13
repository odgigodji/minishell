#include "minishell.h"

int	get_token3(char *line, char **token, t_common *common)
{
	int				count_line;
	int				count_token;
	char			*buffer_token;
	t_token_flag	f;

	get_token_flag_init(&f, &count_line, &count_token, &buffer_token);
	while (buffer_token && line[count_line])
	{
		if (get_token_toggle_flag(&f, line, &count_line))
			continue ;
		if (get_token_is_end(&f, line, count_line))
			break ;
		if (get_token_is_var(&f, line, count_line))
		{
			count_line += expand_variable(&line[count_line],
					common, &buffer_token, &count_token);
			continue ;
		}
		get_token_char(&buffer_token, line, &count_token, &count_line);
		f.back_slash = 0;
	}
	if (!buffer_token || get_token_ret(&f, &buffer_token, count_token, token))
		return (with_error('q'));
	return (count_line);
}

void	lexer_token_post_processing(char **token,
								 char ***result,
								 int *count_result)
{
	if (*token && (*token)[0] != '\0')
	{
		(*result)[*count_result] = *token;
		*count_result += 1;
		(*result)[*count_result] = NULL;
	}
	else if (*token[0] == '\0')
	{
		free(*token);
	}
}

int	get_token_result_proces(char *line, int *count, char **token,
							t_common *common)
{
	int	gt_rv;

	gt_rv = get_token3(&line[*count], token, common);
	if (-1 == gt_rv)
		return (-1);
	*count += gt_rv;
	return (0);
}

char	**lexer(char *line, t_common *common)
{
	int		count;
	int		count_result;
	char	*token;
	char	**result;

	count = 0;
	count_result = 0;
	token = NULL;
	result = malloc(sizeof(char *) * MAX_PATH + 1);
	while (result && line && line[count] && line[count] != ';')
	{
		if (!is_spec_symbol(line[count]))
		{
			if (-1 == get_token_result_proces(line, &count, &token, common))
				return (NULL);
		}
		else
			if (line[count] != ' ')
				count += get_spec_token(&line[count], &token);
		lexer_token_post_processing(&token, &result, &count_result);
		if (line[count] == ' ' && '\0' != line[count])
			count++;
	}
	return (result);
}
