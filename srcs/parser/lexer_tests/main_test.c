//
// Created by Mariam Scot on 3/10/21.
//

#include "test_lexer_00.h"



int	main(int argc, char **argv, char **envp)
{
	t_common	*common;

	common = common_init((char **)envp);
	execute_test_00(common);
	execute_test_01(common);
	return (0);
}