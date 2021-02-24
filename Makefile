NAME	=	minishell

LFT		=	libft.a

LFT_DIR	=	libft

SRC_CMN	:=	$(addprefix srcs/,				\
					main.c					\
					)

SRC_PSR :=	$(addprefix srcs/parser/,		\
						parser.c			\
           			)

SRC_EXR :=	$(addprefix srcs/executor/,		\
           			pre_executer.c			\
           			ft_echo.c				\
           			)

SRC_UTL :=	$(addprefix srcs/utils/,		\
					get_next_line.c			\
					copy_envp.c				\
           			)

SRC		=	$(SRC_CMN) $(SRC_PSR) $(SRC_EXR) $(SRC_UTL)

HEADER	=	minishell.h

OBJ		=	$(SRC:.c=.o)

#	-Wall -Wextra -Werror
CC		=	gcc -Iincludes -Ilibft

.PHONY:		all clean fclean re

all			:$(NAME)

%.o			:%.c $(HEADER)

$(LFT_DIR)/$(LFT):
			$(MAKE) -C $(LFT_DIR)

$(NAME):	$(OBJ) $(LFT_DIR)/$(LFT) includes/$(HEADER)
			$(MAKE) -C $(LFT_DIR)
			$(CC) -L$(LFT_DIR) -lft -o $(NAME) $(OBJ) $(LFT_DIR)/$(LFT)

exa_pip		= srcs/executor/example_pipe.c

srcs/executor/example_pipe.o	:	$(exa_pip) libft/libft.h

example_pipe	:	srcs/executor/example_pipe.o
					$(CC) -L$(LFT_DIR) -lft -o example_pipe srcs/executor/example_pipe.o $(LFT_DIR)/$(LFT)
clean:
			-rm -f $(OBJ)

fclean:		clean
			-rm -f $(NAME)

re:			fclean all
