# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: namerei <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/19 20:47:33 by namerei           #+#    #+#              #
#    Updated: 2021/04/14 01:27:44 by mscot            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strchr.c \
ft_strrchr.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_strnstr.c ft_strdup.c \
ft_calloc.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_itoa.c ft_split.c\
 ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
  ft_isspace.c ft_strrev.c ft_array_len.c ft_lstadd_back.c ft_lstsize.c\
  ft_lstclear.c ft_lstnew.c ft_putendl.c ft_putstr.c ft_strcmp.c\
  ft_putchar.c ft_numlen.c

F_NONE			= \033[37m
F_ORANGE		= \033[38m
F_GREEN         = \033[32m

OBJS	= ${SRCS:.c=.o}
	
NAME	= libft.a

CC		= gcc

RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror  

all:		${NAME}

%.o:	%.c libft.h
			@${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I libft.h

$(NAME):	${OBJS} libft.h ${SRCS} Makefile
			@ar -rc ${NAME} ${OBJS}
			@ranlib ${NAME}
			@#echo "$(F_GREEN)Done! $(F_NONE)"


clean:	
			@${RM} ${OBJS}
#			@echo "$(F_GREEN)Cleaned! $(F_NONE)"

fclean:		clean
			@${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
