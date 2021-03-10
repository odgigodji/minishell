#include "minishell.h"

/*
**	Функция принимает параметр (char **) envp из функции main (argc, argv, envp)
**	находит строку содержащую PATH
**	разбивает её на части
**	используя в качестве разделителя ':'
**	и возвращает массив из строк
**
** 	Строка типа:
**	PATH=/Users/mscot/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki
**
**	Превращается в массив типа:
**	{"/Users/mscot/.brew/bin", "/usr/local/bin", "/usr/bin", "/bin", "/usr/sbin", "/sbin", "/usr/local/munki"}
*/

void	ft_free_list(char ***split_list)
{
	int		count;

	count = 0;
	while ((*split_list)[count] != NULL)
	{
		free((*split_list)[count]);
		count++;
	}
	free((*split_list)[count]);
	free(*split_list);
}

char	**split_path(char **envp)
{
	char 	**path;
	int		count;
	char	link[MAX_PATH];

	count = 0;
	link[0] = '\0';

	while (ft_strncmp(envp[count], "PATH", 4))
		count++;
	ft_strlcpy(link, ft_strrchr(envp[count], '=') + 1, MAX_PATH);
	path = ft_split(link, ':');
	return (path);
}