//
// Created by Mariam Scot on 3/10/21.
//

#ifndef MINISHELL_EXECUTOR_TESTS_H
#define MINISHELL_EXECUTOR_TESTS_H

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

#include "minishell.h"

void	test_get_envp_var_pointer(t_common *common, char **envp);

#endif //MINISHELL_EXECUTOR_TESTS_H
