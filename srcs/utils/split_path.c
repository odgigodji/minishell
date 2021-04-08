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

//char	*get_envp_var_pointer(t_common *common, char *var);

char	**split_path(t_common *common)
{
	char	link[MAX_PATH];
	char	*path_p;

	link[0] = '\0';
	path_p = get_envp_var_pointer(common, "PATH");
	if (path_p)
		return (ft_split(path_p, ':'));
	return (NULL);
}