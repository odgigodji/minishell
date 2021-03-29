#include "minishell.h"


void ft_init_infiles(t_common *common, char *line, int current_command)
{
	int infile_count;

	infile_count = ft_redirect_counter(line, '<'); //fixme
	common->command.simple_commands[current_command]->infile = ft_calloc(sizeof(char *), infile_count + 1);//+1-2
	common->command.simple_commands[current_command]->num_of_infiles = infile_count;
	common->command.simple_commands[current_command]->current_infile = 0;
//	common->command.input_file = ft_calloc(sizeof(char), 255); // fixme test
	common->command.space_after_redirect = 0; // fixme надо или нет

	if (DEBUG_OUTFILE)
		printf(BLU"outfiles_count is %d\n"RESET, common->command.simple_commands[current_command]->num_of_outfiles);
}

/*
** ft_init_outfiles:
 * инициализация outfiles:
 * считаем количество outfiles(= количество '>');
 * выделяем память под все количество файлов;
 * занудяем последний outfile;
 * если у нас только одна simple_command = нет пайпа, ставив флаг have_pipe = 0;
 * если кол-во simple_command > 1 то флаг в положении 1;
*/

void ft_init_outfiles(t_common *common, char *line, int current_command)
{
	int outfile_count;

	outfile_count = ft_redirect_counter(line, '>'); //fixme
	common->command.simple_commands[current_command]->outfile = ft_calloc(sizeof(char *), outfile_count + 1);//+1-2
	common->command.simple_commands[current_command]->num_of_outfiles = outfile_count;
	common->command.simple_commands[current_command]->current_outfile = 0;
//	common->command.input_file = ft_calloc(sizeof(char), 255); // fixme test
	common->command.space_after_redirect = 0; // fixme надо или нет

	if (DEBUG_OUTFILE)
		printf(BLU"outfiles_count is %d\n"RESET, common->command.simple_commands[current_command]->num_of_outfiles);
}

/*
** ft_init_simple_commands:
 * инициализация симпл команды:
 * считаем аргументы симпл команды
 * выделяем память под одну simple_command
 * memory for arguments; // +10 для next_simple_command
 * задаем номер текущего аргумента = 0 тк как формируем новый массив аргументов
 * количество аргуемнтов заносим в структуру
*/

void ft_init_simple_commands(t_common *common, char *line, int current_simple_command)
{
	int arg_count;

	arg_count = ft_arg_counter(line);
	if (DEBUG)
		printf("ft_init_simple_command: arg_count->%d\n", arg_count);
	common->command.simple_commands[current_simple_command] = ft_calloc(sizeof(t_simple_command) , 1);
	common->command.simple_commands[current_simple_command]->arguments = ft_calloc(sizeof(char *),arg_count + 10);
	common->command.simple_commands[current_simple_command]->current_arg = 0;
	common->command.simple_commands[current_simple_command]->arg_count = arg_count;
//	common->command.simple_commands[current_command]->arguments[arg_count] = NULL; ne raskoment
}

/*
 * ft_init_current_command - функция для инициализации команды
 * номер текущей симпл команды, считаем аргументы и количество симпл команд;
 * выделяем память под сипл_команды и и их аргументы;
 * зануляем последнюю симпл_команду;
 * текующая симпл команда = 0;
 * считаем количество аутфайлов и выделяем под них память;
*/

void	ft_init_current_command(t_common *common, char *line)
{
	int current_simple_command;

//	printf("ft_init_current_command_0:|%s|\n", line);
	current_simple_command = common->command.current_simple_command;
	common->command.num_of_simple_commands = ft_simple_command_counter(line); //fixme
	common->command.simple_commands = ft_calloc(sizeof(t_simple_command *),\
	common->command.num_of_simple_commands + 1);// fixme
	ft_init_simple_commands(common, line, current_simple_command);
//	printf("ft_init_current_command_2:|%s|\n", line);
//	printf(BLU"arg_count for 0 simple command is %d\n"RESET, common->command.simple_commands[current_command]->arg_count);
//	printf(GRN"----------------command.num_of_simple_commands is %d------------------\n"RESET, common->command.num_of_simple_commands);
	common->command.simple_commands[common->command.num_of_simple_commands] = NULL;
	common->command.current_simple_command = 0;
	common->command.space_after_redirect = 0;
	ft_init_outfiles(common, line, current_simple_command);
	ft_init_infiles(common, line, current_simple_command);
//	printf("ft_init_current_command_3:|%s|\n", line);
}