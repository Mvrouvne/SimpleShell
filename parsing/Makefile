# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/30 21:04:40 by machaiba          #+#    #+#              #
#    Updated: 2023/05/16 22:55:21 by machaiba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = parsing.a

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address

SRCS = minishell.c\
		ft_lstadd_back.c\
		ft_lstnew.c\
		ft_strcmp.c\
		ft_lstlast.c\
		create_list.c\
		args_count.c\
		check_in_out.c\
		get_next_line.c\
		heredoc.c\
		check_quotes.c\

OBJ =$(SRCS:.c=.o)
CC = cc
# CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	ar -rc $(NAME)  $(OBJ)

clean:
	rm -f $(OBJ)
fclean: clean
	rm -f  $(NAME)

re : fclean all