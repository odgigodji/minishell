/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namerei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 13:49:11 by namerei           #+#    #+#             */
/*   Updated: 2021/04/14 13:54:20 by mscot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_args(char **lexer_result, char *spec_token)
{
	char	**arguments;

	arguments = malloc(
			(num_of_args(lexer_result, spec_token) + 1) * sizeof(char *));
	arguments[num_of_args(lexer_result, spec_token)] = NULL;
	return (arguments);
}

int	num_of_args(char **lexer_result, char *spec_token)
{
	int	num_of_args;
	int	num_of_outfiles;
	int	num_of_infiles;

	num_of_args = 0;
	num_of_outfiles = 0;
	num_of_infiles = 0;
	while (lexer_result[num_of_args]
		&& ft_strcmp(PIPE, lexer_result[num_of_args]))
	{
		if (!ft_strcmp(spec_token, LESS)
			&& (!ft_strcmp(lexer_result[num_of_args], LESS)))
			num_of_infiles++;
		if ((!ft_strcmp(spec_token, GREAT)) \
		&& ((!ft_strcmp(lexer_result[num_of_args], GREAT) \
		|| !ft_strcmp(lexer_result[num_of_args], GREATGREAT))))
			num_of_outfiles++;
		num_of_args++;
	}
	if (!ft_strcmp(spec_token, GREAT))
		return (num_of_outfiles);
	if (!ft_strcmp(spec_token, LESS))
		return (num_of_infiles);
	return (num_of_args);
}

int	num_of_simple_commands(char **lexer_result)
{
	int	count_of_simple_command;

	if (*lexer_result == NULL)
		return (0);
	count_of_simple_command = 1;
	while (lexer_result && *lexer_result)
	{
		if (!ft_strcmp(PIPE, *lexer_result) && *lexer_result + 1)
			count_of_simple_command++;
		lexer_result++;
	}
	return (count_of_simple_command);
}

t_simple_command	**command_table_init(char **lexer_result)
{
	t_simple_command	**command_table;

	command_table = NULL;
	command_table = malloc(
			(num_of_simple_commands(
					lexer_result) + 1) * sizeof(t_simple_command *));
	command_table[num_of_simple_commands(lexer_result)] = NULL;
	return (command_table);
}

t_simple_command	*one_simple_command_init(void)
{
	t_simple_command	*simple_command;

	simple_command = NULL;
	simple_command = malloc(sizeof(t_simple_command));
	simple_command->is_cat = 0;
	return (simple_command);
}
