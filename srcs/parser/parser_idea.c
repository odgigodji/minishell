#include <tcl.h>
#include "minishell.h"

char	**get_infiles(char **lexer_result)
{
	char	**infiles;
	int		counter;

	counter = 0;
	infiles = NULL;
	infiles = init_args(lexer_result, LESS);
	while (lexer_result && *lexer_result && ft_strcmp(*lexer_result, PIPE))
	{
		if (!ft_strcmp(*lexer_result, LESS))
		{
			infiles[counter] = ft_strdup(*(++lexer_result));
			if (!infiles[counter])
				break ;
			counter++;
		}
		lexer_result++;
	}
	infiles[counter] = NULL;
	return (infiles);
}

char	**get_outfiles(char **lexer_result, int *is_cat)
{
	char	**outfiles;
	int		counter;

	counter = 0;
	outfiles = NULL;
	outfiles = init_args(lexer_result, GREAT);
	while (lexer_result && *lexer_result && ft_strcmp(*lexer_result, PIPE))
	{
		if (!ft_strcmp(*lexer_result, GREAT)
			|| !ft_strcmp(*lexer_result, GREATGREAT))
		{
			if (!ft_strcmp(*lexer_result, GREATGREAT))
				*is_cat = 1;
			else
				*is_cat = 0;
			outfiles[counter] = ft_strdup(*(++lexer_result));
			if (!outfiles[counter])
				break ;
			counter++;
		}
		lexer_result++;
	}
	outfiles[counter] = NULL;
	return (outfiles);
}

void	avoid_redirects_without_args(char **lexer_result, int *current_token)
{
	while ((lexer_result[*current_token + 2] && (is_redirect(ACTUAL_TOKEN))) \
	|| (!lexer_result[*current_token + 2] && (is_redirect(ACTUAL_TOKEN))))
	{
		*current_token += 2;
		if (!ACTUAL_TOKEN)
			return ;
	}
}

int	is_redirect(char *actual_token)
{
	if (!ft_strcmp(actual_token, GREAT) || !ft_strcmp(actual_token, GREATGREAT) || \
	!ft_strcmp(actual_token, LESS))
		return (1);
	else
		return (0);
}

void	pass_redirect_files(char **lexer_result, int *current_token)
{
	char	*token_after_file;

	token_after_file = lexer_result[*current_token + 2];
	if (is_redirect(ACTUAL_TOKEN))
	{
		if (((token_after_file && (!is_redirect(token_after_file)))
				|| !token_after_file))
		{
			*current_token += 2;
			return ;
		}
		avoid_redirects_without_args(lexer_result, current_token);
	}
}
