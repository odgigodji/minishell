//
// Created by Mariam Scot on 4/1/21.
//

#include "minishell.h"

char		**braces_expander(char **lexer_result)
{
	return (lexer_result);
}

int	main(int argc, char **argv, char **envp)
{
	char	**lexer_result;
	int		count;
	t_common	*common;

	common = common_init((char **)envp);

	lexer_result = lexer(argv[1]);


	count = 0;
	while (lexer_result[count])
	{
		printf("[%3d] |%10s|\n", count, lexer_result[count]);
		count++;
	}
	return (0);
}