NAME	=	minishell

LFT		=	libft.a

LFT_DIR	=	libft

SRC		:=	$(addprefix srcs/,		\
			main.c					\
			get_next_line.c			\
			pre_executer.c			\
			ft_echo.c				\
			)


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

clean:
			-rm -f $(OBJ)

fclean:		clean
			-rm -f $(NAME)

re:			fclean all
