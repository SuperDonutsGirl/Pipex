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
NAME_BONUS	=		pipex_bonus

###FILES
SRC_MANDA	=		pipex.c 			main.c\
					split.c				utils.c
OBJ_SRC		= 		$(SRC_MANDA:.c=.o)

SRC_BONUS	=		pipex_bonus.c 		main_bonus.c\
					split_bonus.c		utils_bonus.c\
					gnl_bonus.c  		gnl_utils_bonus.c 
OBJ_BONUS	= 		$(SRC_BONUS:.c=.o)


### COMMANDS
CC			=		gcc
FLAGS		=		-g -fsanitize=address -Wall -Wextra -Werror 
RM			=		rm -rf


### NAME
$(NAME)		:		$(OBJ_SRC)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ)

$(NAME_BONUS)		:		$(OBJ_BONUS)
	$(CC) $(FLAGS) -o $(NAME_BONUS) $(OBJ_BONUS)


### RULES
all			:		$(NAME)
bonus 		:		$(NAME_BONUS)
clean		:
	$(RM) $(OBJ_SRC) $(OBJ_BONUS)
fclean		:		clean
	$(RM) $(NAME) $(NAME_BONUS)
re			:		fclean all

.PHONY 		: all bonus clean fclean re