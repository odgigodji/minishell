#include "minishell.h"

t_common	*common_init(char **envp)
{
	t_common	*common;

	common = malloc(sizeof(t_common));
	common->env_variables_list = get_envp(envp);
	common->termcap = t_termcap_init();
	return (common);
}

void	flag_init(t_token_flag *f, int *count)
{
	f->back_slash = 0;
	f->brace_double = 0;
	f->brace_single = 0;
	*count = 0;
}

int		get_semicolon_index(char *line)
{
	int				count;
	t_token_flag	f;

	flag_init(&f, &count);
	while (line[count])
	{
		if (line[count] == '\\')
		{
			f.back_slash = 1;
			count++;
			continue ;
		}
		if (line[count] == '"' && !f.brace_single && !f.back_slash)
			f.brace_double = !f.brace_double;
		if (line[count] == '\'' && !f.brace_double && !f.back_slash)
			f.brace_single = !f.brace_single;
		if (line[count] == ';' && !f.back_slash
			&& !f.brace_single && !f.brace_double)
			break ;
		count++;
		f.back_slash = 0;
	}
	while (ft_isspace(line[count]))
		count++;
	return (count);
}

char	*shift_line(char *line)
{
	char	*line_p;
	int		semicolon_index;
	int		count;

	count = 0;
	if (NULL == line || '\0' == line[0])
		return (line);
	semicolon_index = get_semicolon_index(line);
	if (line[semicolon_index] == ';')
		semicolon_index++;
	line_p = &line[semicolon_index];
	while (line_p[count])
	{
		line[count] = line_p[count];
		count++;
	}
	line[count] = '\0';
	return (line);
}
