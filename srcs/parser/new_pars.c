#include "minishell.h"

int len_for_calloc(char *line, t_common *common, int increment, char *spec)
{
	int len_for_calloc;
	int i;
	int tmp;


	i = increment;
	printf("|%s|\n", line + i);
	len_for_calloc = 0;
//	len_for_calloc = ft_strlen_to_char(line + common->command.simple_commands[0]->i, ' ');
//	len_for_calloc = ft_strlen_to_char(line + common->command.simple_commands[0]->i, '"');
	while(!ft_strchr(spec, line[i]))
	{
		len_for_calloc++;
		i++;
	}
//	if (common->command.simple_commands[0]->k == common->command.simple_commands[0]->command_count)
//		len_for_calloc = ft_strlen(line + i);
//	else
//		common->command.simple_commands[0]->k++;
//	printf("len_for_calloc is %d\n", len_for_calloc);
	return (len_for_calloc);
}

int	make_args(char *line, t_common *common, int increment)
{
	int i;
	int len;
	char spec[6] = " '|\"$";

	i = increment;
//	while(!ft_strchr(spec, line[i]))
//	{
//		printf("%c", line[i]);
//		i++;
//	}
	len = len_for_calloc(line, common, i, spec);
	i += len;
	printf("len_for_calloc is %d\n", len);
	return (i);
}

void line_to_arg(t_common *common, char *line)
{
	int i;

	i = 0;
	common->command.simple_commands[0] = malloc(sizeof(t_simple_command) * 1);
	common->command.simple_commands[0]->k = 0;
	common->command.simple_commands[0]->command_count = 3; // command count
	printf("|%s|\n", line);
	while(line[i] && line[i] != ';')
	{
		if (line[i] == ' ' || line[i] == '"' || line[i] == '\'' || line[i] == '\t' \
		|| line[i] == '|' || line[i] == '$')
			;
		else
		{
//			make_arg(line, common->command.simple_commands[0]);
			i = make_args(line, common, i);
//			printf("%c", line[i]);
		}
		i++;
	}
}

void new_pars(t_common *common, char *line)
{
	char **arg;
	int i;

	i = 0;
	common->command.simple_commands = malloc(sizeof(t_simple_command *) * 5);
//	common->command.simple_commands[0] = sc; //одна команда без пайпов
//	common->command.number_of_simple_commands++;

	line_to_arg(common, line);

//	printf("%s", line);
	exit(0);
}