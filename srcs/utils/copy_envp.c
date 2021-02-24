//
// Created by Mariam Scot on 2/24/21.
//

#include "minishell.h"

/*
** Функция вычисления длинны массива строк
*/

size_t	list_len(const char **list)
{
	size_t	count;

	count = 0;
	while (list[count])
		count++;
	return (count);
}


/*
** Функция копирования списка глобальных переменных envp
**
** Выделяет память достаточную для копирования списка
** копирует envp построчно и
** Возвращает указатель на скопированный список
*/

char	**copy_envp(char const **envp)
{
	size_t	envp_len;
	size_t	line_len;
	char	**copy;
	int 	count;


	envp_len = list_len(envp);
	count = 0;
	if (NULL == (copy = malloc(sizeof(char *) * (envp_len + 1))))
		return (NULL);
	while (count < envp_len)
	{
		line_len = ft_strlen(envp[count]);
		if (NULL == (copy[count] = malloc(line_len + 1)))
		{
			// fixme очистить память списка
			return (NULL);
		}
		ft_strlcpy(copy[count], envp[count], line_len);
		count++;
	}
	return (copy);
}