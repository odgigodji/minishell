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

int invalid_line(char *line)
{
	int i;
	int res;

	res = 0;
	i = 0;
	while(line[i])
	{
//		if(line[i] == ' ')
//			;
//		if (line[i] == '\'' && incorrect_quotes(line + i))
//			return (1);
//		if (line[i] == '|' && incorrect_pipe(line + i))
//			return (1);
		i++;
	}
	return (0);
}