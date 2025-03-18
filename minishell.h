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

typedef struct s_data{
	char **env;
} t_data;

int		ft_strcmp(char *s, char *s2);
char **mod_split(const char *str, char c);
int		single_quote(const char *str, int i);
int		single_quote_dup(const char **str, char **tokens, int *j);
int		double_quote(const char *str, int i);
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

void	free_split(char **split);
char	**free_tokens(char **arr, int j);
/**
***		Error Functions!!!
**/

void	malloc_fail(char *s);

#endif
