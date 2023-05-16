# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otitebah <otitebah@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/16 15:57:14 by otitebah          #+#    #+#              #
#    Updated: 2023/05/16 16:06:11 by otitebah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = execution/execution.a parsing/minishell.a

all : $(NAME)

$(NAME) : $(OBJ)
	cd execution && $(MAKE)
	cd parsing && $(MAKE)

clean :
	rm -f parsing/*.o
	rm -f execution/*.o

fclean : clean
	rm -f parsing/minishell
	rm -f execution/minishell

re : fclean all

push :
	git add .
	git status
	git commit -m "update!"
	git push