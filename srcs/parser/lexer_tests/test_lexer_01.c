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
	printf("\n						");

	char	*line_10 = "echo $SHELL";
	char	*test_result_10[] = {"echo", "/bin/zsh", NULL};
	execute_test_screening(10, line_10, test_result_10, common);

	char	*line_11 = "$SHELL";
	char	*test_result_11[] = {"/bin/zsh", NULL};
	execute_test_screening(11, line_11, test_result_11, common);

	char	*line_12 = "echo \"test\"";
	char	*test_result_12[] = {"echo", "test", NULL};
	execute_test_screening(12, line_12, test_result_12, common);

	char	*line_13 = "echo \"test\\\"\\\"\"";
	char	*test_result_13[] = {"echo", "test\"\"", NULL};
	execute_test_screening(13, line_13, test_result_13, common);

	char	*line_14 = "echo test\\\"";
	char	*test_result_14[] = {"echo", "test\"", NULL};
	execute_test_screening(14, line_14, test_result_14, common);

	char	*line_15 = "echo m\\\"test\\\"";
	char	*test_result_15[] = {"echo", "m\"test\"", NULL};
	execute_test_screening(15, line_15, test_result_15, common);

	char	*line_16 = "echo '\\\\\\'";
	char	*test_result_16[] = {"echo", "\\\\\\", NULL};
	execute_test_screening(16, line_16, test_result_16, common);

	char	*line_17 = "echo \\\\";
	char	*test_result_17[] = {"echo", "\\", NULL};
	execute_test_screening(17, line_17, test_result_17, common);

	char	*line_18 = "echo \\$SHELL";
	char	*test_result_18[] = {"echo", "$SHELL", NULL};
	execute_test_screening(18, line_18, test_result_18, common);

	char	*line_19 = "echo '\\'";
	char	*test_result_19[] = {"echo", "\\", NULL};
	execute_test_screening(19, line_19, test_result_19, common);
	printf("\n						");

	//	echo '\\'
	char	*line_20 = "echo '\\\\'";
	char	*test_result_20[] = {"echo", "\\\\", NULL};
	execute_test_screening(20, line_20, test_result_20, common);

	//	echo '\\\'
	char	*line_21 = "echo '\\\\\\'";
	char	*test_result_21[] = {"echo", "\\\\\\", NULL};
	execute_test_screening(21, line_21, test_result_21, common);

	//	echo '\\\\'
	char	*line_22 = "echo '\\\\\\\\'";
	char	*test_result_22[] = {"echo", "\\\\\\\\", NULL};
	execute_test_screening(22, line_22, test_result_22, common);

	//	echo "\\"
	char	*line_23 = "echo \"\\\\\"";
	char	*test_result_23[] = {"echo", "\\", NULL};
	execute_test_screening(23, line_23, test_result_23, common);

//	echo "test\""
	char	*line_24 = "echo \"test\\\"\"";
	char	*test_result_24[] = {"echo", "test\"", NULL};
	execute_test_screening(24, line_24, test_result_24, common);

//	echo "\\\""		=>	\"
	char	*line_25 = "echo \"\\\"\"";
	char	*test_result_25[] = {"echo", "\"", NULL};
	execute_test_screening(25, line_25, test_result_25, common);

//	echo "\\\""		=>	\"
	char	*line_26 = "echo \\\\\\\"";
	char	*test_result_26[] = {"echo", "\\\"", NULL};
	execute_test_screening(26, line_26, test_result_26, common);

	char	*line_27 = "echo ~\"\"";
	char	*test_result_27[] = {"echo", "~", NULL};
	execute_test_screening(27, line_27, test_result_27, common);

	char	*line_28 = "echo ~";
	char	*test_result_28[] = {"echo", get_envp_var_pointer(common, "HOME"), NULL};
	execute_test_screening(28, line_28, test_result_28, common);

	char	*line_29 = "echo \\n";
	char	*test_result_29[] = {"echo", "n", NULL};
	execute_test_screening(29, line_29, test_result_29, common);

	printf("\n						");
	char	*line_30 = "echo \"\\n\"";
	char	*test_result_30[] = {"echo", "\\n", NULL};
	execute_test_screening(30, line_30, test_result_30, common);

	char	*line_31 = "echo \\\'";
	char	*test_result_31[] = {"echo", "'", NULL};
	execute_test_screening(31, line_31, test_result_31, common);
//	echo $
	char	*line_32 = "echo $";
	char	*test_result_32[] = {"echo", "$", NULL};
	execute_test_screening(32, line_32, test_result_32, common);

	errno = 130;
	char	*line_33 = "echo $?";
	char	*test_result_33[] = {"echo", "130", NULL};
	execute_test_screening(33, line_33, test_result_33, common);
	errno = 0;
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

	lexer_result = lexer(line, common);
	count = 0;
	flag = 0;
	while(lexer_result[count] && test_result[count])
	{
		if (ft_strncmp(lexer_result[count], test_result[count], ft_strlen(test_result[count]) + 1))
		{
			printf("%s "RED"!="RESET" %s | ", lexer_result[count], test_result[count]);
			flag = 1;
		}
		count++;
	}
	return (flag);
}