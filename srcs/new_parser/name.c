#include "minishell.h"

int next_symbol_after_space(const char *line)
{
	int i;

	i = -1;
	while(line[++i])
	{
//		printf("++|%c|+\n", line[i]);
		if (line[i] != ' ' || line[i] == '\\')
			break;
	}
	printf("------|%c|-----\n", line[i]);
	return (line[i]);
}

int with_error(const int unexpected_token)
{
	if (unexpected_token == '\"' || unexpected_token == '\'')
	{
		printf(RED"syntax error : unclosed quote "RESET);
		printf(BLU"'%c'\n"RESET, unexpected_token);
		errno = 42;
	}
	else
	{
		printf(RED"syntax error near unexpected token '%c'\n"RESET, unexpected_token);
		errno = 258;
	}
	return (1);
}

char check_line_1(const char *line, int i, int quotes_flag, char quote_type)
{
	while(line[++i])
	{
		if ((line[i] == '\'' || line[i] == '\"') && quotes_flag == 0)
		{
			quote_type = line[i];
			quotes_flag = 1;
		}
		else if (line[i] == quote_type && quotes_flag == 1)
			quotes_flag = 0;
		if (line[i + 2] && line[i] == '>' && line[i + 1] == '>' && line[i + 2] == '>' && quotes_flag == 0)
			break ;
		if (ft_strchr("{}()&`", line[i]) && quotes_flag == 0)
			break ;
		if(i > 1 && line[i - 1] != '\\' && line[i] == ';' && quotes_flag == 0
		   && (next_symbol_after_space(line + i + 1) == ';'
			   || next_symbol_after_space(line + i + 1) == '|') )
			break ;
		if(i > 1 && line[i - 1] != '\\' && line[i] == '|' && quotes_flag == 0
		   && ( next_symbol_after_space(line + i + 1) == ';'
				|| next_symbol_after_space(line + i + 1) == '|'
				|| next_symbol_after_space(line + i + 1) == '\0'))
			break ;
	}
	if (quote_type && quotes_flag == 1 )
		return (quote_type);
	return (line[i]);
}

int syntax_error(const char *line)
{
//	printf("SE\n");
	int i;
	char is_syntax_error;
	int quotes_flag;
	char quote_type;
	char res;

	quotes_flag = 0;
	quote_type = 0;
	i = -1;
	is_syntax_error = 0;
	if (next_symbol_after_space(line) == ';' || next_symbol_after_space(line) == '|')
	{
		if (next_symbol_after_space(line) == ';')
			return (with_error(';'));
		return (with_error('|'));
	}
	if ((res = check_line_1(line, i, quotes_flag, quote_type)))
		return (with_error(res));
	return (0);
}