#include "minishell.h"

int is_redirects_error(char **lexer_result)
{
	int i;

	i = 0;
	if (is_redirect(lexer_result[ft_array_len(lexer_result) - 1])
	&& !lexer_result[ft_array_len(lexer_result)])
		return (1);

	while(lexer_result[i])
	{
		if(lexer_result[i + 1] && (is_redirect(lexer_result[i]) \
		&& is_redirect(lexer_result[i + 1])))
			return (1);
		i++;
//		if (ft_strcmp(lexer_result[0], PIPE))
//			return (1);
	}
	return (0);
}


int invalid_lexer_result(char **lexer_result)
{
	int counter;

	counter = 0;
	if (!lexer_result || !*lexer_result || !ft_strcmp(*lexer_result, PIPE)) //redirect and null lexer_result
		return (1);
//	if (!ft_strcmp(lexer_result[ft_array_len(lexer_result) - 1], PIPE) && !lexer_result[ft_array_len(lexer_result)]) // second pipe
//		return (1);
//	while(lexer_result[counter]) // if 2 pipes in a row
//	{
//		if(lexer_result[counter + 1] && (!ft_strcmp(lexer_result[counter], PIPE) \
//		&& !ft_strcmp(lexer_result[counter + 1], PIPE)))
//			return (1);
//		counter++;
//	}
	while(lexer_result[counter]) // if 2 pipes in a row
	{
		if(lexer_result[counter + 1] && (!ft_strcmp(lexer_result[counter], PIPE) || is_redirect(lexer_result[counter])) //double pipes or redirects
		&& (!ft_strcmp(lexer_result[counter + 1], PIPE) || is_redirect(lexer_result[counter + 1])))
			return (1);
		if (!lexer_result[counter + 1] && (!ft_strcmp(lexer_result[counter], PIPE) || is_redirect(lexer_result[counter]))) //pipe or redirect is last element
			return (1);
		counter++;
	}
	return (0);
}