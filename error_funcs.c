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

void	no_such_file(char *file)
{
	write_bash();
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	cd_nsf(char *file)
{
	write_bash();
	write(2, "cd: ", 4);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	no_permission(char *file)
{
	write_bash();
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": Permission denied\n", 2);
}

void	command_not_found(t_cmd *cmd, t_data *data)
{
	ft_putstr_fd(cmd->cmd[0], 2);
	close_free_exit(": command not found\n", 127, data, 0);
}

void	export_error(char *s)
{
	write_bash();
	write(2, "export: ", 8);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
}

void	close_free_exit(char *msg, int excode, t_data *data, int parent)
{
	close_pipes_and_files(data, data->first);
	free_all_exit(msg, excode, data, parent);	
}
