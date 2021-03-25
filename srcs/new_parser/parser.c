#include <stdio.h>
#include "minishell.h"

void ft_print_common(t_common *common)
{
	int i = 0;
	int j;
	while(common->command.simple_commands[i])
	{
		j = 0;
		printf(RED"arg_count: %d\n"RESET, common->command.simple_commands[i]->arg_count);
		while(common->command.simple_commands[i]->arguments[j])
		{
			printf(BLU"simple_command[%d]: "RESET, i);
			printf(YEL"sc->arguments[%d]"RESET,j);
			printf(GRN"|%s|\n"RESET, common->command.simple_commands[i]->arguments[j]);
			j++;
		}
		if (common->command.simple_commands[i]->arguments[j] == NULL)
		{
			printf(BLU"simple_command[%d]: "RESET, i);
			printf(YEL"sc->arguments[%d]"RESET,j);
			printf(GRN"|null|\n");
		}
		if ((i + 1) != common->command.num_of_simple_commands)
			printf("--next_simple_command--\n"RESET);
		i++;
	}
	if (common->command.simple_commands[i] == NULL)
		printf(BLU"simple_commands[%d]: (null)\n"RESET, i );
	i = 0;
	j = 0;
//	while(common->command.simple_commands[i]->out_file[j])
//	{
//		while(common->command.simple_commands[i]->out_file[j])
//		{
//			printf(RED"sc[%d] outfile[%d] is |%s|\n"RESET, i, j, common->command.simple_commands[i]->out_file[j]);
//			j++;
//		}
//		i++;
//	}
//	if (common->command.simple_commands[i]->out_file[j] == NULL)
//		printf(RED"sc[%d] outfile[%d] is (null)\n"RESET, i, j);

	if (common->command.simple_commands[0]->num_of_outfiles > 0)
	{
		printf(RED"sc[%d] outfile[%d] is |%s|\n"RESET, 0, 0,
			   common->command.simple_commands[0]->out_file[0]);
		printf(RED"sc[%d] outfile[%d] is |%s|\n"RESET, 0, 0,
			   common->command.simple_commands[0]->out_file[1]);
		printf(RED"sc[%d] outfile[%d] is |%s|\n"RESET, 0, 0,
			   common->command.simple_commands[0]->out_file[2]);
		printf(RED"sc[%d] outfile[%d] is |%s|\n"RESET, 0, 0,
			   common->command.simple_commands[0]->out_file[3]);
		printf(RED"sc[%d] outfile[%d] is |%s|\n"RESET, 0, 0,
			   common->command.simple_commands[0]->out_file[4]);
		printf(RED"sc[%d] outfile[%d] is |%s|\n"RESET, 1, 0,
			   common->command.simple_commands[1]->out_file[0]);
		printf(RED"sc[%d] outfile[%d] is |%s|\n"RESET, 1, 0,
			   common->command.simple_commands[1]->out_file[1]);
		printf(RED"sc[%d] outfile[%d] is |%s|\n"RESET, 1, 0,
			   common->command.simple_commands[1]->out_file[2]);
		printf(RED"sc[%d] outfile[%d] is |%s|\n"RESET, 1, 0,
			   common->command.simple_commands[1]->out_file[3]);
	}
}

int	ft_parser(t_common *common, char *line)
{
	int		ret;

	ret = new_pars(common, line); //--------------- новый парсер
	ft_print_common(common);
	//printf(CYN"-----------------------------------------------------------end of parser----------------------------------------------------\n"RESET);
	return (ret);
}