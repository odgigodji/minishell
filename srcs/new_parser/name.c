#include "minishell.h"

int next_symbol_after_space(const char *line)
{
	int i;

	i = -1;
	while(line[++i])
	{
//		printf("++|%c|+\n", line[i]);
		if (line[i] != ' ' )// || line[i] == '\\')
			break;
	}
//	printf("------|%c|-----\n", line[i]);
	return (line[i]);
}

int with_error(const int unexpected_token)
{
	if (unexpected_token == '\"' || unexpected_token == '\'')
	{
		printf(RED"\nsyntax error : unclosed quotes "RESET);
		printf(BLU"'%c'\n"RESET, unexpected_token);
		errno = 42;
	}
	else
	{
		printf(RED"\nsyntax error near unexpected token "RESET);
		printf(BLU"'%c'\n"RESET, unexpected_token);
		errno = 258;
	}
	return (1);
}

char check_line_2(const char *line, int i, int quotes_flag, char quote_type)
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
		if (quotes_flag == 0 && line[i + 1] && line[i + 2] && line[i] == '>' && line[i + 1] == '>' && line[i + 2] == '>')
			break;
	}
	return (line[i]);
}


int we_are_in_quotes(const char *line, int i)
{
	static int quotes_open = 0;
	static char quote_type = '\0';
	if ((line[i] == '\'' || line[i] == '\"') && quotes_open == 0)
	{
		quote_type = line[i];
		quotes_open = 1;
	}
	else if (line[i] == quote_type && quotes_open == 1)
		quotes_open = 0;
	return (quotes_open);
}

int next_char_is_shielded(const char *line, int *i)
{
	int slash_counter;

//	printf(YEL"-%d\n"RESET, *i);
	slash_counter = 0;
	while(line[*i + 1] && line[*i] == '\\')
	{
		slash_counter++;
		*i += 1;
//		printf(YEL"<%d>\n"RESET, *i);
	}
//	printf(RED"I[%d]\n|%c|\n"RESET, *i, line[*i]);
//	printf(BLU"slash_counter = |%d| slash_counter %% 2 = |%d|\n"RESET, slash_counter, slash_counter % 2);
	if (slash_counter % 2 == 0)
		return (0);
	return (1);
}

char check_line_1(const char *line)
{
	int shield_flag;

	int i = -1;
	while(line[++i])
	{
		shield_flag = 0;
		if (line[i] == '\\' && !we_are_in_quotes(line, i))
			shield_flag = next_char_is_shielded(line, &i);
		if (!we_are_in_quotes(line, i) && !shield_flag)
		{
			if (ft_strchr("{}()&`", line[i]) && !we_are_in_quotes(line, i))
				break ;
			if (line[i] == ';' && !we_are_in_quotes(line, i) && (next_symbol_after_space(line + i + 1) == ';'
					|| next_symbol_after_space(line + i + 1) == '|'))
				break ;
			if (line[i] == '|' && !we_are_in_quotes(line, i) && (next_symbol_after_space(line + i + 1) == ';'
					|| next_symbol_after_space(line + i + 1) == '|'
					|| next_symbol_after_space(line + i + 1) == '\0'))
				break ;
		}
	}
	return (line[i]);
}

int syntax_error(const char *line)
{
//	printf("SE\n");
	int i;
	int quotes_flag;
	char quote_type;
	char res;

	quotes_flag = 0;
	quote_type = 0;
	i = -1;
	if (next_symbol_after_space(line) == ';' || next_symbol_after_space(line) == '|')
	{
		if (next_symbol_after_space(line) == ';')
			return (with_error(';'));
		return (with_error('|'));
	}
	if ((res = check_line_1(line)) || (res = check_line_2(line, i, quotes_flag, quote_type)))
		return (with_error(res));
	return (0);
}