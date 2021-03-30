#include "minishell.h"


int do_all_spec(t_common *common, char *line, char current_char, int increment)
{
	if (current_char == '|')
		do_pipe(common, line); // делаем пайп
	if (current_char == '>')  // || current_char == '<')
		increment += do_redirect(common, line);
	if (current_char == '<')  // || current_char == '<')
		increment += do_r_redirect(common, line);//do_reverse_redirect(common, line);
	if (current_char == '\'')
		increment += do_quotes(common, line);
	increment++; //переходим на следующий элемент
	return (increment);
}