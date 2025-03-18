NAME = minishell
CFLAGS = -Wall -Wextra -Werror
SRCS = minishell.c \
	built_ins.c \
	error_funcs.c \
	free_functs.c \
	ft_strcmp.c \
	ft_strjoin_3.c \
	modified_split.c \
	modified_split_helpers.c \
	parse_input.c \
	putstr_len.c \
	reparse.c \

OBJ = $(SRCS:.c=.o)
RM = rm -f
LIBMINI = libmini.a
LIBFT = -Llibft -lft

all: $(NAME)

$(NAME): $(LIBMINI)
	make -C libft
	cc $(CFLAGS) $(LIBMINI) $(LIBFT) -lreadline -ltinfo -o $(NAME)

$(LIBMINI): $(OBJ)
	ar -rcs $(LIBMINI) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	make -C libft fclean 
	$(RM) $(NAME) $(LIBMINI)

re: fclean all

.PHONY: all clean fclean re
