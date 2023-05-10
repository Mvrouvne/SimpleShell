# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: machaiba <machaiba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/30 21:04:40 by machaiba          #+#    #+#              #
#    Updated: 2023/05/09 15:33:24 by machaiba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g

SRCS = minishell.c\
		ft_lstadd_back.c\
		ft_lstnew.c\
		ft_lstlast.c\
		ft_strncmp.c\

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
			cc $(CFLAGS) $(OBJS) -o $(NAME) -ledit

clean :
		rm -rf $(OBJS)

fclean : clean
		rm -rf $(NAME)

re : fclean all