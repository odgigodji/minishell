//
// Created by Mariam Scot on 4/6/21.
//

#include "test_lexer_00.h"

void	execute_test_01(t_common *common)
{
	printf("\nScreening tests 01\t\t");
	char	*line_00 = "'ec\"\"ho' hello";
	char	*test_result_00[] = {"ec\"\"ho", "hello", NULL};
	execute_test_screening(0, line_00, test_result_00, common);

	char	*line_01 = "'echo' hello";
	char	*test_result_01[] = {"echo", "hello", NULL};
	execute_test_screening(1, line_01, test_result_01, common);

	char	*line_02 = "echo 'hello my dear friend' 1 2";
	char	*test_result_02[] = {"echo", "hello my dear friend", "1", "2", NULL};
	execute_test_screening(2, line_02, test_result_02, common);

	char	*line_03 = "''e''c''h''o'' hello";
	char	*test_result_03[] = {"echo", "hello", NULL};
	execute_test_screening(3, line_03, test_result_03, common);

	char	*line_04 = "'e''c''h''o' hello";
	char	*test_result_04[] = {"echo", "hello", NULL};
	execute_test_screening(4, line_04, test_result_04, common);

	char	*line_05 = "\"ec\"'ho' hello";
	char	*test_result_05[] = {"echo", "hello", NULL};
	execute_test_screening(5, line_05, test_result_05, common);

	char	*line_06 = "\"ec\"'ho' \"\"h\"\"'e'l'l'''o''";
	char	*test_result_06[] = {"echo", "hello", NULL};
	execute_test_screening(6, line_06, test_result_06, common);

	char	*line_07 = "echo \"hel$SHELL\"'$SHELLlo'";
	char	*test_result_07[] = {"echo", "hel/bin/zsh$SHELLlo", NULL};
	execute_test_screening(7, line_07, test_result_07, common);

	char	*line_08 = "echo \"hel$SHELL\"'$?lo'";
	char	*test_result_08[] = {"echo", "hel/bin/zsh$?lo", NULL};
	execute_test_screening(8, line_08, test_result_08, common);

	char	*line_09 = "echo \"hel$?\"'$?lo'";
	char	*test_result_09[] = {"echo", "hel0$?lo", NULL};
	execute_test_screening(9, line_09, test_result_09, common);

	char	*line_10 = "echo $SHELL";
	char	*test_result_10[] = {"echo", "/bin/zsh", NULL};
	execute_test_screening(10, line_10, test_result_10, common);

	char	*line_11 = "$SHELL";
	char	*test_result_11[] = {"/bin/zsh", NULL};
	execute_test_screening(11, line_11, test_result_11, common);

	char	*line_12 = "echo \"test\"";
	char	*test_result_12[] = {"echo", "test", NULL};
	execute_test_screening(12, line_12, test_result_12, common);

//	char	*line_13 = "echo \"test\\\"\"";
//	char	*test_result_13[] = {"echo", "test\\", NULL};
//	execute_test_screening(13, line_13, test_result_13, common);
//
//	char	*line_14 = "echo m\"test\\\"\"";
//	char	*test_result_14[] = {"echo", "mtest\\\"", NULL};
//	execute_test_screening(14, line_14, test_result_14, common);

	char	*line_15 = "echo '\\\\\\'";
	char	*test_result_15[] = {"echo", "\\\\\\", NULL};
	execute_test_screening(15, line_15, test_result_15, common);

	char	*line_16 = "echo \\\\";
	char	*test_result_16[] = {"echo", "\\", NULL};
	execute_test_screening(16, line_16, test_result_16, common);

	char	*line_17 = "echo \\$SHELL";
	char	*test_result_17[] = {"echo", "$SHELL", NULL};
	execute_test_screening(17, line_17, test_result_17, common);
}

void	execute_test_screening(int test_num, char *line, char **test_result, t_common *common)
{
	printf("[%2d ", test_num);
	if (!test_lexer_01_screening(line, test_result, common))
		printf(GRN"ok"RESET"]");
	else
		printf(RED"ng"RESET"]");
}

int	test_lexer_01_screening(char *line, char **test_result, t_common *common)
{
	char	**lexer_result;
	int		count;
	int		flag;

	lexer_result = lexer(line);
	braces_expander(lexer_result, common);
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
}