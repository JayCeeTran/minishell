NAME = minishell
CFLAGS = -Wall -Wextra -Werror
SRCS = minishell.c \
	built_ins.c \
	error_funcs.c \
	free_functs.c \
	ft_strcmp.c \
	modified_split.c \
	modified_split_helpers.c \
	parse_input.c \
	putstr_len.c \
	reparse.c \
	own_test.c \
	read_list.c \
	cut_path_to_bin.c \
	children.c \
	close_fds.c \
	initialize_data.c \
	execute_list_helpers.c \
	echo.c \
	built_in.c \
	my_env.c \

OBJ = $(SRCS:.c=.o)
RM = rm -f
LIBMINI = libmini.a
LIBFT = -Llibft -lft

all: $(NAME)

run: all
	./minishell
fast:
	$(MAKE) -j8

$(NAME): $(LIBMINI)
	make -C libft
	cc $(CFLAGS) $(LIBMINI) $(LIBFT) -lreadline -lncurses -o $(NAME)

$(LIBMINI): $(OBJ)
	ar -rcs $(LIBMINI) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	make -C libft fclean 
	$(RM) $(NAME) $(LIBMINI)

re: fclean all

.PHONY: all clean fclean re run
