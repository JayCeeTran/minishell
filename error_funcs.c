#include "minishell.h"

void	err_msg_exit(char *s, int excode)
{
	if(s)
		ft_putstr_fd(s, 2);
	exit(excode);
}

void	no_closing_quote(void)
{
	ft_putstr_fd("Error: No closing quotes\n", 2);
	exit(EXIT_FAILURE);
}

void	exe_no_permission(t_data *data)
{
	(void)data;
	ft_putstr_fd("-bash: Permission denied\n", 2); //recheck error message
	exit(126);
}

void	write_bash(void)
{
	ft_putstr_fd("-bash: ", 2);
}

void	is_dir_error(char *file)
{
	write_bash();
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": Is a directory\n", 2);
}
