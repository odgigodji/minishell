#include "minishell.h"

int ft_simple_command_counter(char *line) //fixme need upgrade
{
	int counter;

	counter = 1;
	while(*line && *line != ';')
	{
		if (*line == '|')
			counter++;
		line++;
	}
	return (counter);
}

int	ft_arg_counter(char *s)																//fixme если разделитель tab
{
//	printf(BG_WHT"string in ft_arg_counter +%s+\n"RESET, s);
	int c;
	int		count;
	int 	quote_t;
//	char separator[] = " \t";
	char spec[] = "'|\"$;"; // добавил спец символы иду по строке пока невстречаю один из них

	c = ' ';
	count = 0;
	while ((*s && !ft_strchr(spec, *s)))// || (*s == c && *s + 1 == '|'))
	{
//		if ((*s == '"' || *s == '\''))// && *(s - 1) != '\\')
//		{
//			count++;
//			quote_t = *s;
//			s++;
//			while(*s != quote_t)
//			{
//				s++;
//			}
//			s++;
//		}
		if (*s == '>' && *(s + 1) == '>')
			s += 2;
		if(*s =='>' || *s == '<')
			s++;
//		if (((!ft_strchr(sep, *s)) && ft_strchr(spec, *(s + 1 ))) || ((!ft_strchr(sep, *s)) && (*(s + 1) == '\0')) || \
//		((!ft_strchr(sep, *s)) && (*(s + 1 ) == '|')) || ((!ft_strchr(sep, *s) && (*(s + 1 ) == ';')))
		if ((*s != c && *(s + 1) == c) || (*s != c && (*(s + 1) == '\0')) || \
		(*s != c && (*(s + 1 ) == '|')) || (*s != c && (*(s + 1 ) == ';')) || (*s != c && (*(s + 1 ) == '>')\
		|| (*s != c && (*(s + 1 ) == '<')))) //fixme
			count++;
		s++;
	}
	return (count);
}

int ft_redirect_counter(char *line, char redirect_char)
{
	int i;
	int counter;

	i = 0;
	counter = 0;
	while(line[i] && line[i] != ';' && line[i] != '|')
	{
		if (line[i] == redirect_char)
			counter++;
		i++;
	}
	return (counter);
}

int ft_double_redir_counter(char *line)
{
	int i;
	int counter;

	counter = 0;
	i = 0;
	while(line[i] && line[i] != ';' && line[i] != '|')
	{
		if (line[i] == '>' && line[i + 1] == '>' && line[i])
			counter++;
		i++;
	}
	return (counter);
}