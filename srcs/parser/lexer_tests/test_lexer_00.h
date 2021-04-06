//
// Created by Mariam Scot on 4/6/21.
//

#ifndef MINISHELL_02_TEST_LEXER_H
#define MINISHELL_02_TEST_LEXER_H

#include "minishell.h"

void	execute_test_00(void);
int		test_lexer_00_basic(char *line, char **test_result);

void	execute_test_01(t_common *common);
void	execute_test_screening(int test_num, char *line, char **test_result, t_common *common);
int		test_lexer_01_screening(char *line, char **test_result, t_common *common);

#endif //MINISHELL_02_TEST_LEXER_H
