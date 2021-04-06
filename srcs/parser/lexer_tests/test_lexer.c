//
// Created by Mariam Scot on 4/6/21.
//
#include "test_lexer.h"

int	test_lexer_00(char *line, char **test_result)
{
	char	**lexer_result;
	int		count;
	int		flag;

	lexer_result = lexer(line);
	count = 0;
	flag = 0;
	while(lexer_result[count])
	{
		if (ft_strncmp(lexer_result[count], test_result[count], ft_strlen(lexer_result[count]) + 1))
		{
			printf("%s != %s | ", lexer_result[count], test_result[count]);
			flag = 1;
		}
		count++;
	}
	return (flag);
//	braces_expander(lexer_result, common);
}
