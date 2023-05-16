# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/16 15:57:14 by otitebah          #+#    #+#              #
#    Updated: 2023/05/16 23:00:18 by machaiba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FILES = main.c
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
# INCLUDES = execution/execution.a parsing/minishell.a libft/libft.a
EXECUTION = libft/libft.a parsing/parsing.a execution/minishell.a
# PARSING = 
# LIBFT = 

OBJ = $(FILES:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	make -C libft
	make -C parsing
	make -C execution
	$(CC) $(CFLAGS) -lreadline $(EXECUTION) $(OBJ)  -o $(NAME)

clean :
	rm -f main.o
	rm -f libft/*.o
	rm -f parsing/*.o
	rm -f execution/*.o

fclean : clean
	rm -f libft/libft.a
	rm -f parsing/parsing.a
	rm -f execution/minishell.a
	rm -f minishell

re : fclean all

push :
	git add .
	git status
	git commit -m "update!"
	git push