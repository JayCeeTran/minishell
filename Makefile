NAME = minishell
CFLAGS = -Wall -Wextra -Werror
SRCS = minishell.c \
	own_test.c \
	read_list.c \
	built_in.c \
	built_in_logic.c \
	cd.c \
	check_heredoc.c \
	children.c \
	close_fds.c \
	cut_path_to_bin.c \
	error_funcs.c \
	execute_list_helpers.c \
	export.c \
	export_list.c \
	find_correct_bin.c \
	free_functs.c \
	ft_strcmp.c \
	ft_strjoin_3.c \
	initialize_data.c \
	initialize_struct.c \
	my_env.c \
	sort_my_env_to_print.c \
	unset.c \
	parsing.c \
	parsing_sub.c \
	expand.c \
	expand_sub.c \
	tokenize.c \
	tokenize_sub.c \
	tokenize_dollar.c \
	tokenize_qnd.c \
	combined_parser.c \
	merge_token.c \
	find_e_variable.c \
	
OBJ = $(SRCS:.c=.o)
RM = rm -f
LIBMINI = libmini.a
LIBFT = -Llibft -lft

all: $(NAME)

run: all
	./minishell
fast:
	$(MAKE) -j6

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
