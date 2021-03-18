//
// Created by Nelson Amerei on 3/9/21.
//

#include "minishell.h"

//t_simple_command	*simple_command_init(
//		char **arguments,
//		int number_of_arguments,
//		int number_of_available_arguments
//)
//{
//	t_simple_command	*simple_command;
//
//	simple_command = NULL;
//	if (NULL == (simple_command = malloc(sizeof(t_simple_command))))
//		return (NULL);
//	simple_command->arguments = arguments;
//	simple_command->number_of_arguments = number_of_arguments;
//	simple_command->number_of_available_arguments = number_of_available_arguments;
//	return (simple_command);
//}

char *ft_all_str_in_array_join(char **strs)
{
	char *res1;
	char *res2;

	if(strs[0] && strs[1])
		res2 = ft_strjoin(strs[0], strs[1]);
	else if (strs[0])
		return (ft_strdup(strs[0]));
	else
		return ("");
	int i = 2;
	while(strs[i])
	{
		res2 = ft_strjoin(res2, strs[i]);
		i++;
	}
	return(res2);
}

size_t	ft_strlen_to_char(const char *s, char c);

char  *do_dollar_key(char *str, char **env)
{
	printf("str:|%s|\n", str); //path$shell
	char *res;
//	char *env1 = "SECURITYSESSIONID";
//	char *env2 = "SHELL";
	int i = 0;
	int h = 0;
	while(env[h])
	{
		i = 0;
		while (env[h][i])
		{
			printf("%s\n", env[h]);

			if (!(ft_strncmp(env[h], str, ft_strlen_to_char(str, ' '))))
			{
				i += (int)ft_strlen_to_char(env[h], '=') + 1; // + 1 из за знака равно
				printf("\n-----------\nenv[h] + %d = %s\n", i, env[h] + i);
				res = ft_substr(env[h], i , ft_strlen(env[h] + i ));
//				printf("res:%s", res);
//				printf("%s\n", env[h] + i  + 1);//+1 из за знака равно
				printf("%s, ft_strlen res = %d\n---------\n", res, (int)ft_strlen(env[h] + i));
				return (res) ;
			}



			i++;
		}
		h++;
	}

	return ("---trash after $--------"); //				fixme  add some shit need
}

char *do_dollar(char *f_line, char **env, char **arg, int k, int command_count)
{
	char *res;
	int i = 0;

	i++;
	arg[k] = do_dollar_key(f_line + i, env);
	k++;
//			command_count++;
	i += ft_strlen_to_char(f_line + i, ' ');//4; //// 	fixme len of key name
	if (k == command_count)
		i+= ft_strlen(f_line + i);
	printf("len_of_$KEY:%d\n", (int)ft_strlen_to_char(f_line + i, ' '));
//			i += ft_strlen_to_char(f_line[i], ' ');
	printf("after dollar:%s\n", arg[k]);
	printf("!!symbol after dollar rechange:%c\n", f_line[i]);
}

size_t	ft_strlen_to_char(const char *s, char c)
{
	unsigned long len;

	len = 0;
	if (!(ft_strchr(s, c)))
		return (0);
	while (s[len] && s[len] != c)
		len++;
	return ((size_t)len);
}

int	ft_word_counter(char *s, int c)
{
	int		count;
	int 	quote_t;

	count = 0;
	while (*s)
	{
		if ((*s == '"' || *s == '\''))// && *(s - 1) != '\\')
		{
			count++;
			quote_t = *s;
			s++;
			while(*s != quote_t)
			{
				s++;
			}
			s++;
		}
		if ((*s != c && *(s + 1) == c) || (*s != c && (*(s + 1) == '\0')))
			count++;
		s++;
	}
	return (count);
}

void **line_to_arguments(char *line, char *env[4], t_simple_command *sc)
{
//	int i;
//	int j;
//	int k;
	int e;
//	int flag;
//	int command_count;
//	char **arguments;
	char *f_line;
	int len_for_calloc;
	char spec[5] = " '|\"";
	int memory_allocated;
//	t_simple_command scmd;
	t_command cmd;

	sc->i = 0;
	sc->j = 0;
	sc->k = 0;
//	e = 0;
//	line = "echo f f f  s fd g sdf g sdfgsdf g sdfg sd fg sd f f f  s fd g sdf g sdfgsdf g sdfg sd fg sd f f f  s fd g sdf g sdfgsdf g sdfg sd fg sd f f f  s fd g sdf g sdfgsdf g sdfg sd fg sd f f f  s fd g sdf g sdfgsdf g sdfg sd fg sd f f f  s fd g sdf g sdfgsdf g sdfg sd fg sd v v f f f  s fd g sdf g sdfgsdf g sdfg sd fg sd f f f  s fd g sdf g sdfgsdf g sdfg sd fg sd f f f  s fd g sdf g sdfgsdf g sdfg sd fg sd f f f  s fd g sdf g sdfgsdf g sdfg sd fg sd f f f  s fd g sdf g sdfgsdf g sdfg sd fg sd f f f  s fd g sdf g sdfgsdf g sdfg sd fg sd v v f f f  s fd g sdf g sdfgsdf g sdfg sd fg sd f f f  s fd g sdf g sdfgsdf g sdfg sd fg sd f f f  s fd g sdf g sdfgsdf g sdfg sd fg sd f f f  s fd g sdf g sdfgsdf g sdfg sd fg sd f f f  s fd g sdf g sdfgsdf g sdfg sd fg sd f f f  s fd g sdf g sdfgsdf g sdfg sd fg sd v v f f f  s fd g sdf g sdfgsdf g sdfg sd fg sd f f f  s fd g sdf g sdfgsdf g sdfg sd fg sd f f f  s fd g sdf g sdfgsdf g sdfg sd fg sd f f f  s fd g sdf g sdfgsdf g sdfg sd fg sd f f f  s fd g sdf g sdfgsdf g sdfg sd fg sd f f f  s fd g sdf g sdfgsdf g sdfg sd fg sd v v f f f  s fd g sdf g sdfgsdf g sdfg sd fg sd f f f  s fd g sdf g sdfgsdf g sdfg sd fg sd f f f  s fd g sdf g sdfgsdf g sdfg sd fg sd f f f  s fd g sdf g sdfgsdf g sdfg sd fg sd f f f  s fd g sdf g sdfgsdf g sdfg sd fg sd f f f  s fd g sdf g sdfgsdf g sdfg sd fg sd v v f f f  s fd g sdf g sdfgsdf g sdfg sd fg sd f f f  s fd g sdf g sdfgsdf g sdfg sd fg sd f f f  s fd g sdf g sdfgsdf g sdfg sd fg sd f f f  s fd g sdf g sdfgsdf g sdfg sd fg sd f f f  s fd g sdf g sdfgsdf g sdfg sd fg sd f f f  s fd g sdf g sdfgsdf g sdfg sd fg sd v v ";

	sc->memory_allocated = 0;
	printf("line:|%s|\n", line);
	f_line = ft_strtrim(line, " ");

	printf("line:|%s|\n", line);
	printf("f_line:|%s|\n", f_line);

//	return (0);
	sc->arg_count = ft_word_counter(f_line, ' '); // 			fixme quoters moment
	sc->arguments = ft_calloc(sizeof(char *),sc->arg_count + 1 ); // память под двойной массив

	printf("command_count = %d\n", sc->arg_count);
	sc->flag = 0; // нет попадания в пробел

//	spec = " '|\"";

//	printf("spec:%s\n", spec);

//	printf("word number is: %d\n" , ft_word_counter(line, ' '));

//	arguments[0] = ft_calloc(sizeof(char ), 10); // выделяем память под аргументы
//	arguments[1] = ft_calloc(sizeof(char ), 10);
//	arguments[2] = ft_calloc(sizeof(char ), 10);

//	arguments[3] = ft_calloc(sizeof(char ), 10);
//	arguments[4] = ft_calloc(sizeof(char ), 10);

//	arguments[0][0] = 'l';
//	arguments[0][1] = 's';

//	arguments[0] = "|ls|";
//	arguments[1] = "|-l|";
//	arguments[2] = "|-a|";

	sc->arguments[sc->arg_count] = NULL; // последний аргумент
	sc->quotes = 0;
	int fl = 0;
	int h = 0;
//	printf("1\n");
	while(f_line[sc->i] && f_line[sc->i] != ';' )
	{
//		printf("2\n");
		if (f_line[sc->i] == '"')
		{
			h = 0;
			sc->i++;
			int ln = ft_strlen_to_char(f_line + sc->i, '"');
			printf("ln after quotes is %d\n", ln);
			sc->arguments[sc->k] = ft_calloc(sizeof(char), ln);
//			ft_substr(f_line, i, ft_strlen_to_char(f_line + i, '"'));
			while(f_line[sc->i] != '"')
			{
				sc->arguments[sc->k][h] = f_line[sc->i];
//				printf("|-%c-|\n", arguments[k][h]);
				sc->i++;
				h++;
			}
			sc->arguments[sc->k][h] = '\0';
			printf("--%s--\n", sc->arguments[sc->k]);
			if (sc->k < sc->arg_count)
				sc->k++; // 													fixme
			sc->i++;
		}
		if ((f_line[sc->i] == ' ' || f_line[sc->i] == '\t') && !sc->quotes)
		{
			if (sc->k < sc->arg_count && sc->flag == 0) // должны быть меньше количетсва аргументов ровно или - 1
			{
				sc->flag  = 1;
				sc->j = 0;
				sc->k++;
				sc->memory_allocated = 0;
			}
//			printf("k:%d\n", k);
//			i++;
		}
//		else if (f_line[i] == '$') //									fixme  work on that
//		{
////			char *res;
//
//			i++;
//			sc->arguments[k] = do_dollar_key(f_line + i, env);
//			k++;
////			command_count++;
//			i += ft_strlen_to_char(f_line + i, ' ');//4; //// 			fixme len of key name
//			if (k == command_count)
//				i+= ft_strlen(f_line + i);
//			printf("len_of_$KEY:%d\n", (int)ft_strlen_to_char(f_line + i, ' '));
////			i += ft_strlen_to_char(f_line[i], ' ');
//			printf("after dollar:%s\n", sc->arguments[k]);
//			printf("!!symbol after dollar rechange:%c\n", f_line[i]);
//
//		}
		else if (f_line[sc->i])
		{
//			printf("2.1\n");
			make_arg(f_line, sc);
		}
//		printf("-----%s----\n", sc->arguments[sc->k]);
		sc->i++;
	}
//	printf("3\n");
	free(f_line);
	sc->arguments[sc->arg_count] = NULL; //		ass				fixme incorrect command_count
//	arguments[4][7] = '\0';
//	printf("%s\n", arguments[4]);
//	printf("i is: %d\n", sc->i);
//	sc->arguments[sc->k][sc->j] = '\0';
//	arguments[2][10] = '\0';

//	arguments[4] = NULL;
//	sc->i = 0;
//	while(sc->arguments[i])
//	{
//		printf("%d argument is |%s|\n", i, sc->arguments[i]);
//		i++;
//	}
//
//	return (arguments);
}

int pars(t_common *common, char *line)
{
	t_simple_command *sc;
	char **arg;
	char *env[6];
//	t_data data[5];
//	data[0].str = "hello";
//	data[0].iterator = 0;
//	data[0].str = line;
	int i;

	i = 0;
//	char line[] = " echo \"hello world $PATH lalal\" 123 $PATH $SHELL $qwe $OLDPWD 456 a";
	sc = ft_calloc(sizeof(t_simple_command) , 1);
//	printf("word number is: %d\n" , ft_word_counter(line, ' '));
//	t_command command;

//	simple_command = ft_calloc(sizeof(t_simple_command), 1); // numbers of commands

//	simple_command->number_of_arguments = 2;
//	arguments = ft_calloc(sizeof(char **),3);
//	arguments[0] = "|ls|";
//	arguments[1] = "|-l|";
//	arguments[2] = "|-a|";
//	arguments[3] = NULL;
//	simple_command->arguments = arguments;
//	while(simple_command->arguments[i])
//	{
//		printf("%s\n", simple_command->arguments[i]);
//		i++;
//	}

	env[0] = "PATH=/Users/namerei/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki";
	env[1] = "SHELL=/bin/zsh";
	env[2] = "SECURITYSESSIONID=186a8";
	env[3] = "OLDPWD=/lol";
	env[4] = "qwe=/kakdela";
	env[5] = NULL;


	line_to_arguments(line, env, sc);
//	printf("!%d!\n", (int)ft_strlen_to_char("line12345   ;", ' '));

//	sc = simple_command_init(arguments, 1, 1);
//	printf("%d argument is |%s|\n", 0, sc->arguments[0]);
//	while(sc->arguments[i])
//	{
//		printf("%d argument is |%s|\n", i, sc->arguments[i]);
//		i++;
//	}

	i = 0;
	common->command.simple_commands = malloc(sizeof(t_simple_command *) * 5);
	common->command.simple_commands[0] = sc; //одна команда без пайпов
	common->command.number_of_simple_commands++;
	printf("\n-------test zone------\n");



//	char *test_line = "12345hello67890";
//	int d = ft_strlen_to_char("0df6", '6');
//	printf("d is %d\n", d);

//	int e = 0;
//	while(env[e])
//	{
////		printf("%d:%s\n", e, env[e]);
////		printf("%d:%s\n", e, envp[e]);
//		e++;
//	}
//
//	e = 0;
//	char **args = ft_calloc(sizeof(char *), 20);
//	while(*args)
//	{
//		args = ft_calloc(sizeof(char), 100);
//		args++;
//	}
//	//do_first_arg
//	args[0] = arguments[0];
//
//	//do_seocnd_arg
//
//	while(arguments[e])
//	{
//		if (arguments[e][0] == '$')
//		{
//			printf("%s\n",arguments[e]);
//		}
//		e++;
//	}
//
//	char *arg_2;
//
//
////	arg_2 = ft_strjoin(arg[1], arg[2]);//
//	arg_2 = ft_all_str_in_array_join(arguments + 1);
//	printf("first arguments:%s\n", args[0]);
//	printf("second_arg:%s\n", arg_2);

//	char *res;
//	char *env1 = "SECURITYSESSIONID";
////	char *env2 = "SHELL";
//	int h = 0;
//	while(env[h])
//	{
//		i = 0;
//		while (env[h][i])
//		{
////			i = 0;
//			if (!ft_strncmp(env[h], env1, ft_strlen(env1)))
//			{
//				i += ft_strlen_to_char(env[h], '=') + 1; // + 1 из за знака равно
//				printf("env[h] + %d = %s\n", i, env[h] + i);
//				res = ft_substr(env[h], i , ft_strlen(env[h] + i ));
////				printf("%s\n", env[h] + i  + 1);//+1 из за знака равно
//				printf("%s, ft_strlen res = %d\n", res, ft_strlen(env[h] + i));
//				break ;
//			}
//			i++;
//		}
//		h++;
//	}

//	printf("\n--------------------------\n");



//	command.number_of_available_simple_commands = 1;
//	command.number_of_simple_commands = 1;


//	printf("line:|%s|\n", line);
//	skip_spaces(&data[0]);
//
//	printf("\nI:%d\n", data[0].iterator);



//printf("--------------------------------\n");
//char *line1 = "echo $PATH \"hello\" ";
//i = 0;
//while(line1[i])
//{
//	if (line1[i] == '$')
//	{
//		printf("+");
//		i += 5;
//	}
//	if (line[i] == '"')
//		printf("-");
//	else
//		printf("%c", line1[i]);
//	i++;
//}

//	printf("--%s--\n", do_dollar_key("PATH$SHELL  echo etc", env));

//while (1) ;
}
