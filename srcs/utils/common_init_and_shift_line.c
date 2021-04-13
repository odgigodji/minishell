#include "minishell.h"

t_common	*common_init(char **envp)
{
	t_common	*common;

	common = malloc(sizeof(t_common));
	common->env_variables_list = get_envp(envp);
	common->env_variables = envp;
	common->termcap = t_termcap_init();
	return (common);
}

int		get_semicolon_index(char *line)
{
	int		count;
	int		flag_brace_single;
	int		flag_brace_double;
	int		flag_slash;

	count = 0;
	flag_brace_double = 0;
	flag_brace_single = 0;
	flag_slash = 0;
	while (line[count])
	{
		if (line[count] == '\\')
		{
			flag_slash = 1;
			count++;
			continue ;
		}
		if (line[count] == '"' && !flag_brace_single && !flag_slash)
			flag_brace_double = !flag_brace_double;
		if (line[count] == '\'' && !flag_brace_double && !flag_slash)
			flag_brace_single = !flag_brace_single;
		if (line[count] == ';' && !flag_slash && !flag_brace_single && !flag_brace_double)
			break ;
		count++;
		flag_slash = 0;
	}
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
