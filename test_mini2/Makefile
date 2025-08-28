NAME = minishell
CFLAGS = -g2 -Wall -Wextra -Werror
SRCS = minishell.c \
	add_env_var_helpers.c \
	read_list.c \
	built_in.c \
	built_in_logic.c \
	cd.c \
	cd_utils.c \
	check_heredoc.c \
	children.c \
	close_fds.c \
	cut_path_to_bin.c \
	create_pwd_if_doesnt_exist.c \
	env_strlen.c \
	error_funcs.c \
	error_funcs_2.c \
	error_funcs_3.c \
	execute_list_helpers.c \
	export.c \
	export_list.c \
	find_correct_bin.c \
	find_bin_helper.c \
	find_pwds_cd_helper.c \
	find_pwd_from_env.c \
	fork_for_heredoc.c \
	free_functs.c \
	free_funcs_2.c \
	free_funcs_3.c \
	free_tokens_all_exit.c \
	ft_strcmp.c \
	ft_strjoin_3.c \
	heredoc_error.c \
	initialize_data.c \
	initialize_struct.c \
	is_path_valid.c \
	my_env.c \
	path_in_env.c \
	print_export.c \
	sort_my_env_to_print.c \
	unset.c \
	valid_char_funcs.c \
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
	syntax_error.c \
	
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
