#include "minishell.h"

void ft_do_command(t_common *common)
{
	char		**lexer_result;
	int 		gnl_rv;

	if (common->termcap->line[0] == '\0')
	{
		prompt();
		gnl_rv = t_get_next_line(&common->termcap->line, common->termcap);
		to_cannon();

		if ((common->termcap->line[0] == 0) && 1 == gnl_rv)
			mini_exit(common);
		if (syntax_error(common->termcap->line))
		{
			common->termcap->line[0] = '\0';
			return ;
		}
		write(1, "\n", 1);
	}
	if (NULL == (lexer_result = lexer(common->termcap->line, common)))
	{
		shift_line(common->termcap->line); //line =
		return ;
	}
	if (invalid_lexer_result(lexer_result))
	{
		common->termcap->line[0] = '\0';
		return ;
	}
	common->command = get_command_table(lexer_result);
	shift_line(common->termcap->line);
	executor(common);
	free_lexer_results(&lexer_result);
	free(lexer_result);
	free_command_table(common);
}

void	minishell_loop(char **envp)
{
	t_common	*common;

	common = common_init((char **)envp);
	signal_processor();
	while (1)
	{
		ft_do_command(common);
	}
}

int main(int argc, char const **argv, char const **envp)
{
	(void)argc;
	(void)argv;
	g_errno = 0;
	setbuf(stdout, NULL);

	minishell_loop((char **)envp);
	return (0);
}