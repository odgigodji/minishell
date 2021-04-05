#include "minishell.h"

int is_redirects_error(char **lexer_result)
{
	int i;

	i = 0;
	while(lexer_result[i])
	{
		if(lexer_result[i + 1] && (!ft_strcmp(lexer_result[i], GREAT) \
		|| !ft_strcmp(lexer_result[i], LESS) || !ft_strcmp(lexer_result[i], GREATGREAT))\
		&& (!ft_strcmp(lexer_result[i + 1], GREAT) \
		|| !ft_strcmp(lexer_result[i + 1], LESS) || !ft_strcmp(lexer_result[i + 1], GREATGREAT)))
			return (1);
		i++;
//		if (ft_strcmp(lexer_result[0], PIPE))
//			return (1);
	}
	return (0);
}

int ft_is_valid_line(char *line)
{
	;
}

int invalid_lexer_result(char **lexer_result)
{
	if (is_redirects_error(lexer_result))
		return (1);
	return (0);
}