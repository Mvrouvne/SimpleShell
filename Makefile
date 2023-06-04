
NAME = minishell


FILES = main.c\
		execution/builtins/builtins.c\
		execution/builtins/export_a.c\
		execution/commands.c\
		execution/ft_lstadd_front.c\
		execution/ft_strcpy.c\
		execution/save_env.c\
		execution/builtins/cd.c\
		execution/builtins/export.c\
		parsing/minishell.c\
		parsing/args_count.c\
		parsing/check_in_out.c\
		parsing/check_quotes.c\
		parsing/create_list.c\
		parsing/ft_lstadd_back.c\
		parsing/ft_lstlast.c\
		parsing/ft_lstnew.c\
		parsing/ft_strcmp.c\
		parsing/get_next_line.c\
		parsing/heredoc.c\
		parsing/ft_chrjoin.c\
		parsing/expand.c\
		parsing/errors_check.c\
		

INCLUDES = libft/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g
# INCLUDES = execution/execution.a parsing/minishell.a libft/libft.a

# PARSING = 
# LIBFT = 

OBJ = $(FILES:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	make -C libft
	$(CC) $(CFLAGS) $(OBJ) $(INCLUDES) -lreadline -o $(NAME)	

clean :
	rm -f main.o
	rm -f libft/*.o
	rm -f parsing/*.o
	rm -f execution/*.o
	rm -f execution/builtins/*.o

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