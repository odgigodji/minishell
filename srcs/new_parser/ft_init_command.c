#include "minishell.h"

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

//	common->command.simple_commands[current_command]->num_of_outfiles = ft_redirect_counter(line, '>'); //fixme для отсальных типов добавить
	common->command.simple_commands[current_command]->out_file = ft_calloc(sizeof(char *), outfile_count);
	common->command.simple_commands[current_command]->out_file[outfile_count] = NULL;
	common->command.simple_commands[current_command]->num_of_outfiles = outfile_count;
	common->command.simple_commands[current_command]->current_outfile = 0;
	printf(BLU"redirect_count is %d\n"RESET, common->command.simple_commands[current_command]->num_of_outfiles);
	if (common->command.num_of_simple_commands == 1)
		common->command.simple_commands[current_command]->have_pipe = 0; //eсли есть пайп
	else
		common->command.simple_commands[current_command]->have_pipe = 1; //обнуляем пайп
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

void ft_init_simple_commands(t_common *common, char *line, int current_command)
{
	int arg_count;

	arg_count = ft_arg_counter(line);
	//printf("->%d\n", arg_count);
	common->command.simple_commands[current_command] = ft_calloc(sizeof(t_simple_command) , 1);
	common->command.simple_commands[current_command]->arguments = ft_calloc(sizeof(char *),arg_count + 1);
	common->command.simple_commands[current_command]->current_arg = 0;
	common->command.simple_commands[current_command]->arg_count = arg_count;
	common->command.simple_commands[current_command]->arguments[arg_count] = NULL;
	//printf(BLU"arg_count for simple command[%d] is %d\n"RESET, current_command, common->command.simple_commands[current_command]->arg_count);
}

/*
 * ft_init_current_command - функция для инициализации команды
 * номер текущей команды, считаем аргументы и количество симпл команд;
 * выделяем память под сипл_команды и и их аргументы;
 * зануляем последнюю симпл_команду;
 * текующая симпл команда = 0;
 * считаем количество аутфайлов и выделяем под них память;
*/

void	ft_init_current_command(t_common *common, char *line)
{
	int current_command;

	current_command = common->command.current_simple_command;
	common->command.num_of_simple_commands = ft_simple_command_counter(line); //fixme
	common->command.simple_commands = ft_calloc(sizeof(t_simple_command *),\
	common->command.num_of_simple_commands + 1);// fixme
	ft_init_simple_commands(common, line, current_command);
//	printf(BLU"arg_count for 0 simple command is %d\n"RESET, common->command.simple_commands[current_command]->arg_count);
//	printf(GRN"----------------command.num_of_simple_commands is %d------------------\n"RESET, common->command.num_of_simple_commands);
	common->command.simple_commands[common->command.num_of_simple_commands] = NULL;
	common->command.current_simple_command = 0;
	ft_init_outfiles(common, line, current_command);
}