#include "minishell.h"

void	get_token_flag_init(t_token_flag *f, int *count_line, int *count_token)
{
	f->brace_single = 0;
	f->brace_double = 0;
	f->back_slash = 0;
	*count_line = 0;
	*count_token = 0;
}

int	get_token_is_end(t_token_flag *f, char *line, int count_line)
{
	if ('\0' == line[count_line]
		|| ((line[count_line] == ' '
				|| is_spec_symbol(line[count_line]))
			&& !f->back_slash
			&& !f->brace_single
			&& !f->brace_double))
		return (1);
	return (0);
}

int	get_token_is_var(t_token_flag *f, char *line, int count_line)
{
	if ((line[count_line] == '~'
			|| (line[count_line] == '$'
				&& (ft_isalnum(line[count_line + 1])
					|| ft_strchr("?_", line[count_line + 1]))))
		&& !f->brace_single
		&& !f->back_slash)
		return (1);
	return (0);
}

int	get_token_ret(t_token_flag *f,
					 char **buffer_token,
					 int count_token,
					 char **token)
{
	(*buffer_token)[count_token] = '\0';
	*token = strdup(*buffer_token);
	free(*buffer_token);
	if (f->brace_single || f->brace_double || f->back_slash)
		return (1);
	return (0);
}

void	get_token_char(char **buffer_token,
					   char *line,
					   int *count_token,
					   int *count_line)
{
	(*buffer_token)[*count_token] = line[*count_line];
	*count_line += 1;
	*count_token += 1;
}
