#include <stdio.h>
#include "minishell.h"

void ft_print_common(t_common *common, int flag)
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

	while(common->command.simple_commands[i] && i < common->command.num_of_simple_commands)
	{
		j = 0;
		printf(GRN"simple_comand [%d]\n"RESET, i);
		printf(BLU"num_of_outfiles:%d\n"RESET, common->command.simple_commands[i]->num_of_outfiles);
		while(common->command.simple_commands[i]->outfile[j] && j < common->command.simple_commands[i]->num_of_outfiles)
		{
			printf(RED"sc[%d] outfile[%d] is |%s|\n"RESET, i, j, common->command.simple_commands[i]->outfile[j]);
			j++;
		}
		if (common->command.simple_commands[i]->outfile[j] == NULL)
		{
			printf(RED"sc[%d] outfile[%d] is (null)\n"RESET, i, j);
		}
		i++;
	}
//	printf(YEL"final output_file is |%s|\n"RESET, common->command.infile);

	i = 0;
	while(common->command.simple_commands[i] && i < common->command.num_of_simple_commands)
	{
		j = 0;
		printf(GRN"simple_comand [%d]\n"RESET, i);
		printf(BLU"num_of_infiles:%d\n"RESET, common->command.simple_commands[i]->num_of_infiles);
		while(common->command.simple_commands[i]->infile[j] && j < common->command.simple_commands[i]->num_of_infiles)
		{
			printf(YEL"sc[%d] infile[%d] is |%s|\n"RESET, i, j, common->command.simple_commands[i]->infile[j]);
			j++;
		}
		if (common->command.simple_commands[i]->infile[j] == NULL)
		{
			printf(YEL"sc[%d] infile[%d] is (null)\n"RESET, i, j);
		}
		i++;
	}
//	printf(YEL"final input_file is |%s|\n"RESET, common->command.infile);
//	if (common->command.simple_commands[0]->num_of_outfiles > 0)
//	{
//		printf(RED"sc[%d] outfile[%d] is |%s|\n"RESET, 0, 0,
//			   common->command.simple_commands[0]->outfile[0]);
//		printf(RED"sc[%d] outfile[%d] is |%s|\n"RESET, 0, 0,
//			   common->command.simple_commands[0]->outfile[1]);
//		printf(RED"sc[%d] outfile[%d] is |%s|\n"RESET, 0, 0,
//			   common->command.simple_commands[0]->outfile[2]);
//		printf(RED"sc[%d] outfile[%d] is |%s|\n"RESET, 0, 0,
//			   common->command.simple_commands[0]->outfile[3]);
//		printf(RED"sc[%d] outfile[%d] is |%s|\n"RESET, 0, 0,
//			   common->command.simple_commands[0]->outfile[4]);
//
//		printf(RED"sc[%d] outfile[%d] is |%s|\n"RESET, 1, 0,
//			   common->command.simple_commands[1]->outfile[0]);
//		printf(RED"sc[%d] outfile[%d] is |%s|\n"RESET, 1, 0,
//			   common->command.simple_commands[1]->outfile[1]);
//		printf(RED"sc[%d] outfile[%d] is |%s|\n"RESET, 1, 0,
//			   common->command.simple_commands[1]->outfile[2]);
//		printf(RED"sc[%d] outfile[%d] is |%s|\n"RESET, 1, 0,
//			   common->command.simple_commands[1]->outfile[3]);
//	}
}

int	ft_parser(t_common *common, char *line)
{
	int		ret;

	ret = new_pars(common, line);

	if (FINAL_PRINT)
	{
		ft_print_common(common, 1);
		printf(CYN"-----------------------------------------------------------end of parser----------------------------------------------------\n"RESET);
	}
	return (ret);
}