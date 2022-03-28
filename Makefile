# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pamartin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/28 15:59:58 by pamartin          #+#    #+#              #
#    Updated: 2022/03/28 16:00:01 by pamartin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		pipex

###FILES
SRC			=		pipex.c 		main.c\
					split.c			utils.c

OBJ			= 		$(SRC:.c=.o)


### COMMANDS
CC			=		gcc
FLAGS		=		-g -fsanitize=address -Wall -Wextra -Werror 
RM			=		rm -rf


### NAME
$(NAME)		:		$(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ)


### RULES
all			:		$(NAME)
clean		:
	$(RM) $(OBJ)
fclean		:		clean
	$(RM) $(NAME)
re			:		fclean all
