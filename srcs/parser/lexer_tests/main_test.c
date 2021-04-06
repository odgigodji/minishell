//
// Created by Mariam Scot on 3/10/21.
//

#include "test_lexer.h"

int	main(int argc, char **argv, char **envp)
{
	t_common	*common;

	common = common_init((char **)envp);
	test_lexer(common, envp);
	return (0);
}