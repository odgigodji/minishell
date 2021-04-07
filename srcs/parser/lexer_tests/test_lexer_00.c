//
// Created by Mariam Scot on 4/6/21.
//
#include "test_lexer_00.h"

int	test_lexer_00_basic(char *line, char **test_result, t_common *common)
{
	char	**lexer_result;
	int		count;
	int		flag;

	lexer_result = lexer(line, common);
	count = 0;
	flag = 0;
	while(lexer_result[count] && test_result[count])
	{
		if (ft_strncmp(lexer_result[count], test_result[count], ft_strlen(lexer_result[count]) + 1))
		{
			printf("%s "RED"!="RESET" %s ~|~ ", lexer_result[count], test_result[count]);
			flag = 1;
		}
		count++;
	}
	return (flag);
//	braces_expander(lexer_result, common);
}

void	execute_test(int test_num, char *line, char **test_result, t_common *common)
{
	printf("[%2d ", test_num);
	if (!test_lexer_00_basic(line, test_result, common))
		printf(GRN"ok"RESET"]");
	else
		printf(RED"ng"RESET"]");
}

void	execute_test_00(t_common *common)
{
	printf("Basic tests 00\t\t\t");
	char	*line_00 = "cat -e < file < test";
	char	*test_result_00[] = {"cat", "-e", LESS, "file", LESS, "test", NULL};
	execute_test(0, line_00, test_result_00, common);

	char	*line_01 = "export test+=test";
	char	*test_result_01[] = {"export", "test+=test", NULL};
	execute_test(1, line_01, test_result_01, common);

	char	*line_02 = "export test1 = test1";
	char	*test_result_02[] = {"export", "test1", "=", "test1", NULL};
	execute_test(2, line_02, test_result_02, common);

	char	*line_03 = "cat -e < file < test";
	char	*test_result_03[] = {"cat", "-e", LESS, "file", LESS, "test", NULL};
	execute_test(3, line_03, test_result_03, common);

	char	*line_04 = "cat < file < test | cat -e";
	char	*test_result_04[] = {"cat", LESS, "file", LESS, "test", PIPE, "cat", "-e", NULL};
	execute_test(4, line_04, test_result_04, common);

	char	*line_05 = "cat < file < test | sort";
	char	*test_result_05[] = {"cat", LESS, "file", LESS, "test", PIPE, "sort", NULL};
	execute_test(5, line_05, test_result_05, common);

	char	*line_06 = "ls |ls |ls|ls| echo hello world|echo hello world";
	char	*test_result_06[] = {"ls", PIPE, "ls", PIPE, "ls", PIPE, "ls", PIPE, "echo", "hello", "world", PIPE, "echo", "hello", "world", NULL};
	execute_test(6, line_06, test_result_06, common);

	char	*line_07 = "echo hello > outfile0 1 2 | echo world > outfile1 3 4";
	char	*test_result_07[] = {"echo", "hello", GREAT, "outfile0", "1", "2", PIPE, "echo", "world", GREAT, "outfile1", "3", "4", NULL};
	execute_test(7, line_07, test_result_07, common);

	char	*line_08 = "echo hello > outfile-0-0 1 2";
	char	*test_result_08[] = {"echo", "hello", GREAT, "outfile-0-0", "1", "2", NULL};
	execute_test(8, line_08, test_result_08, common);

	char	*line_09 = "echo a> out01 b c";
	char	*test_result_09[] = {"echo", "a", GREAT, "out01", "b", "c", NULL};
	execute_test(9, line_09, test_result_09, common);

	char	*line_10 = "echo hello> outfile-0-0 1 2 | echo world >outfile-1-0 3 4";
	char	*test_result_10[] = {"echo", "hello", GREAT, "outfile-0-0", "1", "2", PIPE, "echo", "world", GREAT, "outfile-1-0", "3", "4", NULL};
	execute_test(10, line_10, test_result_10, common);

	char	*line_11 = "echo 0 > out0 > echo 1 > out1 > echo 2 > out2 > echo 3 > out3 > echo 4 > out4 > echo 5 > out5";
	char	*test_result_11[] = {"echo", "0", GREAT, "out0", GREAT, "echo", "1", GREAT, "out1", GREAT, "echo", "2", GREAT, "out2", GREAT, "echo", "3", GREAT, "out3", GREAT, "echo", "4", GREAT, "out4", GREAT, "echo", "5", GREAT, "out5", NULL};
	execute_test(11, line_11, test_result_11, common);

	char	*line_12 = "";
	char	*test_result_12[] = {NULL};
	execute_test(12, line_12, test_result_12, common);

	char	*line_13 = "ls -l";
	char	*test_result_13[] = {"ls", "-l", NULL};
	execute_test(13, line_13, test_result_13, common);

	char	*line_14 = "echo hello >> aaa 1 2 3 | echo 12 << asdf dfdf | echo 12 > asdf dfdf";
	char	*test_result_14[] = {"echo", "hello", GREATGREAT, "aaa", "1", "2", "3", PIPE, "echo", "12", GREATLESS, "asdf", "dfdf", PIPE, "echo", "12", GREAT, "asdf", "dfdf", NULL};
	execute_test(14, line_14, test_result_14, common);

	char	*line_15 = "echo hello world >> 1 << 2 >> 3";
	char	*test_result_15[] = {"echo", "hello", "world", GREATGREAT, "1", GREATLESS, "2", GREATGREAT, "3", NULL};
	execute_test(15, line_15, test_result_15, common);

	char	*line_16 = "echo kitty | cat -e";
	char	*test_result_16[] = {"echo", "kitty", PIPE, "cat", "-e", NULL};
	execute_test(16, line_16, test_result_16, common);

	char	*line_17 = "echo hello|echo 123";
	char	*test_result_17[] = {"echo", "hello", PIPE, "echo", "123", NULL};
	execute_test(17, line_17, test_result_17, common);

	char	*line_18 = "echo $?";
	char	*test_result_18[] = {"echo", "0", NULL};
	execute_test(18, line_18, test_result_18, common);

	char	*line_19 = "echo -n -n -n -n test";
	char	*test_result_19[] = {"echo", "-n", "-n", "-n", "-n", "test", NULL};
	execute_test(19, line_19, test_result_19, common);

	char	*line_20 = "echo kitty|cat -e";
	char	*test_result_20[] = {"echo", "kitty", PIPE, "cat", "-e", NULL};
	execute_test(20, line_20, test_result_20, common);

	char	*line_21 = "echo kitty'|'cat -e";
	char	*test_result_21[] = {"echo", "kitty|cat", "-e", NULL};
	execute_test(21, line_21, test_result_21, common);

	char	*line_22 = "echo $\"PWD\"";
	char	*test_result_22[] = {"echo", "PWD", NULL};
	execute_test(22, line_22, test_result_22, common);

	char	*line_23 = "echo 1 >> 2";
	char	*test_result_23[] = {"echo", "1", GREATGREAT, "2", NULL};
	execute_test(23, line_23, test_result_23, common);

	char	*line_24 = "echo 1 > < 2";
	char	*test_result_24[] = {"echo", "1", GREAT, LESS, "2", NULL};
	execute_test(24, line_24, test_result_24, common);

	char	*line_25 = "echo \"test\\\"\"";
	char	*test_result_25[] = {"echo", "test\"", NULL};
	execute_test(25, line_25, test_result_25, common);

	char	*line_26 = "echo m\"test\\\"\"";
	char	*test_result_26[] = {"echo", "mtest\"", NULL};
	execute_test(26, line_26, test_result_26, common);
}
