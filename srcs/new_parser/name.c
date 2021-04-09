#include "minishell.h"

int incorrect_quotes(char *line)
{
	printf(RED"---------|%s|---------\n"RESET, line);
	int i;
	int flag;
	int res;

	i = 1;
	res = 1;
	while (line[i])
	{
		if (line[i] == '\'')
			res++;
//		if (line[i + 1] && line[i] == '\\' && line[i + 1] == '\'')
//			res--;
		i++;
	}
	if (res % 2)
	{
		printf("[%d]not_ok\n", res);
		return (1);
	}
	if (!(res % 2))
	{
		printf("[%d]ok\n", res);
	}
//	if (res % 2)
//	exit(5);
	return (0);
}

int semi_column_error(const char *line)
{
	printf("sem\n");
	int i;
	int j;
	int flag = 0;
	int res = 0;

	i = 0;
	while(line[i])
	{
		if (line[i] == ';'  )
		{
			flag = 1;
			res++;
		}
		else
		{
			flag = 0;
			res = 0;
		}
		i++;
	}
	return (0);
}

//int incorrect_pipe(const char *line)
//{
//	int i;
//
//	i = 1;
//	while(line[i])
//	{
//		if (ft_empty_line(line))
//			return 1;
//		if(line[i] != '|' || (line[i + 1] && line[i] == ' ' && line[i + 1] != '|'))
//			return(0);
//		i++;
//	}
//	return(1);
//}

int next_symbol_after_space(const char *line)
{
	int i;

	i = -1;
	while(line[++i])
	{
//		printf("++|%c|+\n", line[i]);
		if (line[i] != ' ')
			break;
	}
	printf("------|%c|-----\n", line[i]);
	return (line[i]);
}

int syntax_error(const char *line)
{
//	printf("SE\n");
	int i;
	int is_syntax_error;
	int quotes_flag;

	quotes_flag = 0;
	i = -1;
	is_syntax_error = 0;
	while(line[++i])
	{
//		if (line[i] == '\'' || line[i] == '\"')
//		{
//			quotes_flag = 1;
//			while(line[++i] != )
//		}
		if(line[i] == ';' && (next_symbol_after_space(line + i + 1) == ';'
		|| next_symbol_after_space(line + i + 1) == '|') )
			is_syntax_error++;
		if(line[i] == '|' && ( next_symbol_after_space(line + i + 1) == ';'
		|| next_symbol_after_space(line + i + 1) == '|' || next_symbol_after_space(line + i + 1) == '\0'))
			is_syntax_error++;
//		if(line[i] == ';' && (line[i + 1] == ';' || line[i + 1] == '|'))
//			is_syntax_error++;
	}
	if(is_syntax_error)
	{
		printf(RED"syn error\n"RESET);
		errno = 258;
		return (1);
	}
	return (0);
}