//
// Created by Mariam Scot on 3/10/21.
//

#include "executor_tests.h"

int	main(int argc, char **argv, char **envp)
{
	t_common	*common;

	common = common_init((char **)envp);
	test_get_envp_var_pointer(common, envp);
	return (0);
}