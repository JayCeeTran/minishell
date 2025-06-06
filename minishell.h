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

typedef struct s_redir{
	char *redir;
	char *file;
	int pipe;
	struct s_redir *next;
} t_redir;

typedef struct s_cmd{
	char **cmd;
	struct s_redir *redirections;
	struct s_cmd *next;
} t_cmd;

typedef struct s_pipes{
	int *cur_p;
	int *new_p;
	int *temp_p;
} t_pipes;

typedef struct s_data{
	char **env;
	char **my_env;
	char **path;
	char *heredoc_path;
	t_cmd *list;
	t_pipes *pipe_pointers;
	int pipe1[2];
	int pipe2[2];
	int file[2];
	int first;
	int o_stdin;
	int o_stdout;
	int status;
} t_data;

typedef struct s_built_ins{
	char *name;
	int (*func)(t_data *, t_cmd *);
} t_built_ins;

/**
***		EXECUTION!
**/


void	add_cmd(t_cmd **head, t_cmd *newnode);
t_cmd	*newcmd(char **cmd, t_redir *directions);
void	add_redir(t_redir **head, t_redir *newnode);
t_redir *new_redir(char *redir, char *file, int pipe);
char	**new_command(char *s, char *s2, char *s3);
void	testing(char **env);

void	read_list(t_data *data);
void	check_heredoc(t_redir *dir, t_data *data);
char 	*save_heredoc_path(t_data *data);
void	my_envp(t_data *data);
void	find_path(t_data *data, char **env);
char	*find_bin(t_cmd *cmd, t_data *data);
char	*append_to_path(t_cmd *cmd, t_data *data);
int	check_existence_permission(char *s, t_data *data, t_cmd *cmd);
void	swap_pipes(t_pipes *pipes, int first);
void	new_pipes(t_pipes *pipes, t_data *data);
void	fork_helper(pid_t pid, t_data *data, t_cmd *cur, t_pipes *pipes);

/**
***		BUILT INS!!!
**/
int	built_ins_parent(t_data *data, t_cmd *cmd);
int	built_ins(t_data *data, t_cmd *cmd);
int	b_echo(t_data *data, t_cmd *cmd);
int	b_pwd(t_data *data, t_cmd *cmd);
int	b_env(t_data *data, t_cmd *cmd);
int	b_export(t_data *data, t_cmd *cmd);
int	b_unset(t_data *data, t_cmd *cmd);
int	b_exit(t_data *data, t_cmd *cmd);
int	b_cd(t_data *data, t_cmd *cmd);
void	initialize_struct(t_built_ins *built_ins);
//void	add_env_var(t_data *data, char *s);
//void	del_env_var(t_data *data, char *s);
int	envp_size(char **env);
/**
***		CHILDREN!!!
**/
void	children(t_data *data, t_cmd *cmd, t_pipes *pipes);	
void	close_fds(int *fd);
void	close_pipes_and_files(t_data *data, int first);
t_cmd	*initialize_data(t_data *data, t_pipes *pipes);
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

void	free_list(t_data *data);
void	free_redir(t_redir *directs);
void	free_all_exit(char *s, int excode, t_data *data);
void	free_split_exit(char **cmd);
void	free_split(char **split);
char	**free_tokens(char **arr, int j);
/**
***		Error Functions!!!
**/
void	is_dir_error(char *file);
void	err_msg_exit(char *s, int excode);
void	no_closing_quote(void);
void	write_bash();
void	no_such_file(char *file);
void	cd_nsf(char *file);
void	is_dir_error(char *file);
void	no_permission(char *file);
void	command_not_found(t_cmd *cmd, t_data *data);
void	close_free_exit(char *msg, int excode, t_data *data);
void	export_error(char *s);
#endif
