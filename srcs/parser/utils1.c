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
	while(lexer_result[counter])
	{
		if(lexer_result[counter + 1] && (!ft_strcmp(lexer_result[counter], PIPE) || is_redirect(lexer_result[counter])) //double pipes or redirects
		&& (!ft_strcmp(lexer_result[counter + 1], PIPE) || is_redirect(lexer_result[counter + 1])))
			return (with_error('r'));
		if (!lexer_result[counter + 1] && is_redirect(lexer_result[counter])) //pipe or redirect is last element
			return (with_error('r'));
		counter++;
	}
	return (0);
}

void ft_kitty(char *line_is_kitty)
{
	if (!ft_strcmp(line_is_kitty, "kitty"))
		printf(CYN"\n"
			   "	  ／＞　  フ\n"
			   "　　　　　| 　_　 _|\n"
			   "　 　　　／`ミ _x 彡\n"
			   "　　 　 /　　　 　 |\n"
			   "　　　 /　 ヽ　　 ﾉ\n"
			   "　／￣|　　 |　|　|\n"
			   "　| (￣ヽ＿_ヽ_)_)\n"
			   "　＼二つ"RESET);
}