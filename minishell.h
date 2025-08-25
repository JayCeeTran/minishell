#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <curses.h>
# include <term.h>

// HOANGS PART!
typedef struct s_token
{
        char    *token;
        int             is_operator;
        struct s_token  *next;
}       t_token;

// END OF HOANGS PART!

typedef struct s_redir{
	char *redir;
	char *file;
	int expand;
	struct s_redir *next;
} t_redir;

typedef struct s_cmd{
	char **cmd;
	t_redir *redirections;
	int pipe;
	struct s_cmd *next;
} t_cmd;

typedef struct s_pipes{
	int *cur_p;
	int *new_p;
	int *temp_p;
} t_pipes;

typedef struct s_heredoc{
	char *path[18];
	int count;
} t_heredoc;

typedef struct s_data{
	char **env;
	char **my_env;
	char **export_list;
	char **path;
	t_heredoc *heredoc;
	t_cmd *list;
	t_pipes *pipe_pointers;
	int pipe1[2];
	int pipe2[2];
	int file[2];
	int first;
	int o_stdin;
	int o_stdout;
	int status;
	int lineno;
} t_data;

typedef struct s_built_ins{
	char *name;
	int (*func)(t_data *, t_cmd *, int parent);
} t_built_ins;

// HOANG FUNCS!
/*t_token *tokenize(const char *s);
void    expand_token(t_token *token, t_data *data);
t_cmd   *parse_cmd_list(t_token *tokens);
t_cmd	 *parse(char *line, t_data *data);
void    append_char(char **dst, char c);
char    *get_env_value(char *key, char **envp);
char    *ft_strjoin_free(char *s1, char *s2);
int     is_valid_var_char(char c);
void	simplify_tokens(t_token **head);
*/
int     has_dollar(char *s);
int		is_valid_var_char(char c);
int		is_op_char(char c);
t_token	*new_token_str(const char *s, size_t len, int is_op);
void	append_token(t_token **head, t_token *node);
void	tokenize_dollar(const char *s, int *i, t_token **head, int outside_single);
int		tokenize_quotes_or_dollar(const char *s, int *i, t_token **head);
t_token	*tokenize(const char *s);
char	*ft_strjoin_free(char *s1, char *s2);
void	append_char(char **dst, char c);
char	*get_env_value(char *key, char **envp);
char	*expand_node(char *input, t_data *data);
void	expand_token(t_token **tokens, t_data *data);
void	simplify_tokens(t_token **head);
void	fill_redirections(t_cmd *cmd, t_token *start, t_token *end);
char	**fill_cmd_array(t_token **cur);
t_cmd	*parse_cmd_list(t_token *tokens);
void 	free_token(t_token *head);
void	free_cmd_list(t_cmd *head);
t_cmd	*parse(char *line, t_data *data);

/**
***		EXECUTION!
**/

//		MY OWN TESTING FOR COMMANDS
void	add_cmd(t_cmd **head, t_cmd *newnode);
t_cmd	*newcmd(char **cmd, t_redir *directions, int pipe);
void	add_redirr(t_redir **head, t_redir *newnode);
t_redir *new_redir(char *redir, char *file);
char	**new_command(char *s, char *s2, char *s3);
void	testing(char **env);


void	read_list(t_data *data);
void	check_heredoc(t_redir *dir, t_data *data);
char 	*save_heredoc_path(t_data *data, char *heredoc);
void	my_envp(t_data *data);
void	find_path(t_data *data, char **env);
char	*find_bin(t_cmd *cmd, t_data *data);
char	*append_to_path(t_cmd *cmd, t_data *data);
int	check_existence_permission(char *s, t_data *data, t_cmd *cmd);
void	swap_pipes(t_pipes *pipes, int first);
void	new_pipes(t_pipes *pipes, t_data *data);
void	fork_helper(pid_t pid, t_data *data, t_cmd *cur, t_pipes *pipes);
char 	*find_e_variable(char *var, t_data *data, int len);
void	unlink_heredocs(t_heredoc *heredoc);
/**
***		BUILT INS!!!
**/
int	built_ins_parent(t_data *data, t_cmd *cmd);
int	built_ins(t_data *data, t_cmd *cmd);
int	b_echo(t_data *data, t_cmd *cmd, int parent);
int	b_pwd(t_data *data, t_cmd *cmd, int parent);
int	b_env(t_data *data, t_cmd *cmd, int parent);
int	b_export(t_data *data, t_cmd *cmd, int parent);
int	b_unset(t_data *data, t_cmd *cmd, int parent);
int	b_exit(t_data *data, t_cmd *cmd, int parent);
int	b_cd(t_data *data, t_cmd *cmd, int parent);

/**
***	BUILT IN HELPERS
**/
void add_to_export_list(t_data *data, char *s, int parent);
int	env_strlen(char *s);
int add_env_helper(t_data *data, char ***new_env, char *s, int parent);
void remove_from_export_list(t_data *data, char *s, int parent);
void	initialize_struct(t_built_ins *built_ins);
int	envp_size(char **env);
void	sort_my_env(t_data *data, int parent);
void	print_export_list(char **list);
int	cd_home(t_data *data, t_cmd *cmd, char *opwd, int parent);
int	unset_strcmp(char *s1, char *s2);
void    make_my_env_freeable(t_data *data, char *opwd, int index, int env_size);
void    find_home_from_my_env(t_data *data, char **home);
void change_dir_helper(t_data *data, char *opwd, int parent);
void	count_arguments_and_print_list(t_data *data, t_cmd *cmd, int parent);
void	print_my_env_with_quotes(char *s);
int	malloc_new_list_return_old_size(t_data *data, char ***new_env, int parent);

/**
***		CHILDREN!!!
**/
void	children(t_data *data, t_cmd *cmd, t_pipes *pipes);	
void	close_fds(int *fd);
void	close_pipes_and_files(t_data *data, int first);
t_cmd	*initialize_data(t_data *data, t_pipes *pipes, t_heredoc *heredoc);
void	fill_fds(t_redir *redir, t_data *data);
int		infile_permission(char *file, int *data_file);
int		outfile_permission(char *file, int redir, int *data_file);
void	redirections(t_pipes *pipes, t_data *data, int flag);


/**
***		PARSING
**/

int		ft_strcmp(char *s, char *s2);
char	*ft_strjoin_3(char *s, char *s2, char *s3);
char **mod_split(const char *str, char c);
int		single_quote(const char *str, int *i);
int		single_quote_dup(const char **str, char **tokens, int *j);
int		double_quote(const char *str, int *i);
int		double_quote_dup(const char **str, char **tokens, int *j);
void	putstr_len(char *s, int fd, int len);
void	parse_input(char *s, t_data *data);
void	compare_inputs(char **command);
char **reparse(char **cmd, t_data *data);

/**
***		Build in commands!!!
**/

void	exit_cmd(char **cmd);
void	echo_cmd(char **cmd);

/**
***		Free Functions!!!
**/
void	free_heredoc_paths(t_heredoc *heredoc);
void	free_list(t_data *data);
void	free_redir(t_redir *directs);
void	free_token(t_token *token);
void	free_all_exit(char *s, int excode, t_data *data, int parent);
void	free_split_exit(char **cmd);
void	free_split(char **split);
void	free_split_index(char **split, int n);
char	**free_tokens(char **arr, int j);
/**
***		Error Functions!!!
**/
//void	is_dir_error(char *file);
void	malloc_fail(t_data *data, char **new_env, int parent);
void	err_msg_exit(char *s, int excode);
void	no_closing_quote(void);
void	write_bash();
void	no_such_file(char *file);
void	cd_nsf(char *file);
void	is_dir_error(char *file);
void	no_permission(char *file);
void	command_not_found(t_cmd *cmd, t_data *data);
void	close_free_exit(char *msg, int excode, t_data *data, int parent);
void	export_error(char *s);
void	cd_error_msg(t_data *data, t_cmd *cmd, int error, int *status_changed);
#endif
