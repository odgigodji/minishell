NAME	=	minishell

LFT		=	libft.a

LFT_DIR	=	libft

SRC_CMN	:=	$(addprefix srcs/,				\
						main.c				\
						)
						

SRC_BLD :=	$(addprefix srcs/buildins/,		\
						mini_cd.c			\
						mini_echo.c			\
						mini_env.c			\
						mini_exit.c			\
						mini_export.c		\
						mini_hello.c		\
						mini_pwd.c			\
						mini_unset.c		\
						)

SRC_EXR :=	$(addprefix srcs/executor/,		\
						execute_command.c	\
						executor.c			\
						executor_pipe.c		\
						)

SRC_LXR :=	$(addprefix srcs/lexer/,		\
						lexer_get_token.c	\
						lexer_m.c			\
						lexer_utils.c		\
						)

SRC_PSR :=	$(addprefix srcs/parser/,		\
						get_command.c		\
						name.c				\
						parser_idea.c		\
						parser_m.c			\
						utils_3.c			\
						)

SRC_SGN :=	$(addprefix srcs/signals/,		\
						signals_handler.c	\
						)

SRC_TRM :=	$(addprefix srcs/termcap/,			\
						termcap.c				\
						termcap_history.c		\
						termcap_init.c			\
						termcap_input_signal.c	\
						termcap_key_handle.c	\
						)

SRC_UTL :=	$(addprefix srcs/utils/,					\
						common_init_and_shift_line.c	\
						free_all.c						\
						get_envp_variable.c				\
						get_envp_variable_update.c		\
						get_envp_variable_utils.c		\
						make_envp.c						\
						open_file.c						\
						prompt.c						\
						split_path.c					\
						utils.c							\
						)

SRC		=	$(SRC_CMN) $(SRC_BLD) $(SRC_EXR) $(SRC_LXR)	\
			$(SRC_PSR) $(SRC_SGN) $(SRC_TRM) $(SRC_UTL)

HEADER	=	minishell.h

OBJ		=	$(SRC:.c=.o)

CC		=	gcc -Wall -Wextra -Werror -Iincludes -Ilibft 

.PHONY:	all clean fclean re
all:	$(NAME)

$(NAME):	$(OBJ) $(LFT_DIR)/$(LFT) Makefile
			$(CC) -L$(LFT_DIR) -lft -ltermcap -o $@ $(OBJ) 

%.o			:	%.c $(HEADER)

libft/libft.a:
			make -C $(LFT_DIR)

clean:
			make clean -C $(LFT_DIR)
			-rm -f $(OBJ)

fclean:		clean
			make fclean -C $(LFT_DIR)
			-rm -f $(NAME)

re:			fclean all

