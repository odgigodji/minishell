#include "minishell.h"

void ft_init_outfiles(t_common *common, char *line, int current_command)
{
	int outfile_count;

	outfile_count = ft_redirect_counter(line, '>');

//	common->command.simple_commands[current_command]->outfile_count = ft_redirect_counter(line, '>'); //fixme для отсальных типов добавить
	common->command.simple_commands[current_command]->out_file = ft_calloc(sizeof(char *), outfile_count); //fixme функция для этого
	common->command.simple_commands[current_command]->out_file[outfile_count] = NULL; //занудяем последний outfile
	common->command.simple_commands[current_command]->outfile_count = outfile_count;
	printf(BLU"redirect_count is %d\n"RESET, common->command.simple_commands[current_command]->outfile_count);
	if (common->command.number_of_simple_commands > 1)
		common->command.simple_commands[current_command]->have_pipe = 1; //eсли есть пайп
	else
		common->command.simple_commands[current_command]->have_pipe = 0; //обнуляем пайп
}

/*
** инициализация симпл команды
*/

void ft_init_simple_commands(t_common *common, char *line, int current_command)
{
	int arg_count;

	arg_count = ft_arg_counter(line);	//считаем аргументы симпл команды
	//printf("->%d\n", arg_count);
	common->command.simple_commands[current_command] = \
	ft_calloc(sizeof(t_simple_command) , 1); //выделяем память под одну simple_command
	common->command.simple_commands[current_command]->arguments = \
	ft_calloc(sizeof(char *),arg_count + 1); // memory for arguments; // +10 для next_simpl_command
	common->command.simple_commands[current_command]->current_arg = 0;//задаем номер текущего аргумента = 0 тк как формируем новый массив аргументов
	common->command.simple_commands[current_command]->arg_count = arg_count; // количество аргуемнтов заносим в структуру
	common->command.simple_commands[current_command]->arguments[arg_count] = NULL; //0
	//printf(BLU"arg_count for simple command[%d] is %d\n"RESET, current_command, common->command.simple_commands[current_command]->arg_count);
}

/*
** функция для инициализации команды
*/

void	ft_init_current_command(t_common *common, char *line)
{
	int current_command;

	current_command = common->command.current_simple_command; //номер текущей команды, считаем аргументы и количество симпл команд------------------
	common->command.number_of_simple_commands = ft_simple_command_counter(line); //fixme
	common->command.simple_commands = ft_calloc(sizeof(t_simple_command *),\
	common->command.number_of_simple_commands + 1); // выделяем память под сипл_команды и и их аргументы fixme
	ft_init_simple_commands(common, line, current_command);
//	printf(BLU"arg_count for 0 simple command is %d\n"RESET, common->command.simple_commands[current_command]->arg_count);
//	printf(GRN"----------------command.number_of_simple_commands is %d------------------\n"RESET, common->command.number_of_simple_commands);
	common->command.simple_commands[common->command.number_of_simple_commands] = NULL; // зануляем последнюю симпл_команду
	common->command.current_simple_command = 0; // текующая симпл команда = 0;

	ft_init_outfiles(common, line, current_command);
	//-------------------------------считаем количество аутфайлов и выделяем под них память-----------------
//	common->command.simple_commands[current_command]->out_file = ft_calloc(sizeof(char *), 3); //fixme функция для этого

}