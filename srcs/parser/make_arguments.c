#include "minishell.h"

int make_arg(char *f_line , t_simple_command *sc)
{
	int len_for_calloc;
//	int j;

	len_for_calloc = 0;
	printf("2.2\n");
	printf("%d\n", sc->memory_allocated);
	if (!sc->memory_allocated)
	{
		printf("2.3\n");
		len_for_calloc = (sc->k == sc->command_count - 1) ? \
				ft_strlen(f_line + sc->i) : ft_strlen_to_char(f_line + sc->i, ' ');

		sc->arguments[sc->k] = ft_calloc(sizeof(char), len_for_calloc + 1); // +1 для \0

		printf("for k= %d elem - len_for_calloc : %d\n", sc->k , len_for_calloc);
		sc->memory_allocated = 1;
	}
//			printf("arguments[%d] len_for_calloc : %d\n", k, len_for_calloc);

	sc->arguments[sc->k][sc->j] = f_line[sc->i];
//			printf("------\n");// заполняем строки
//			printf("arguments[%d][%d] is '%c'\n", k, j, arguments[k][j]);
//			printf("f_line[%d] is '%c'\n", i, f_line[i]);
//			printf("------\n");
	sc->j++;
	sc->flag = 0;
	return 0;
}
