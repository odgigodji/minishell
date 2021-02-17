# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mscot <mscot@student.21-school.ru>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/08 21:46:16 by mscot             #+#    #+#              #
#    Updated: 2021/02/17 19:13:52 by mscot            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

LFT		=	libft.a

LFT_DIR	=	libft

SRC		:=	$(addprefix srcs/,		\
			main.c					\
			)


HEADER	=	minishell.h

OBJ		=	$(SRC:.c=.o)

CC		=	gcc -Wall -Wextra -Werror -Iincludes -Ilibft

.PHONY:		all clean fclean re

all			:$(NAME)

%.o			:%.c $(HEADER)

$(LFT_DIR)/($LFT):
			$(MAKE) -C $(LFT_DIR)

$(NAME):	$(OBJ) $(LFT_DIR)/$(LFT) includes/$(HEADER)
			$(CC) -L$(LFT_DIR) -lft -o $(NAME) $(OBJ) $(LFT_DIR)/$(LFT)

clean:
			-rm -f $(OBJ)

fclean:		clean
			-rm -f $(NAME)

re:			fclean all
