#include "minishell.h"

void	b_echo(t_data *data, char **cmd)
{
	int i;
	int nl;

	i = 1;
	nl = 1;
	if(cmd[1] && ft_strcmp(cmd[1], "-n") == 0)
	{
		nl = 0;
		i++;
	}
	while(cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if(cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if(nl)
		write(1, "\n", 1);
	close_pipes_and_files(data->file, data->pipe2, data->pipe1, data->first);
	free_all_exit("", 0, data);
}

void	b_pwd(t_data *data)
{
	char *pwd;

	pwd = getenv("PWD");
	if(!pwd)
	{
		close_pipes_and_files(data->file, data->pipe2, data->pipe1, data->first);
		free_all_exit("Failed to get pwd\n", 1, data);
	}
	ft_putstr_fd(pwd, 1);
	write(1, "\n", 1);
}

void	b_env(t_data *data)
{
	int i;

	i = 0;
	while(data->env[i])
	{
		ft_putstr_fd(data->env[i], 1);
		write(1, "\n", 1);
		i++;
	}
}

int		b_export(t_data *data, t_cmd *cmd)
{
	int i;
	t_redir *cur;

	i = 1;
	cur = cmd->redirections;
	while(cur)
	{
		fill_fds(cur, data);
		if(data->file[0] == -1 || data->file[1] == -1)
			return(1);
		if(cur->pipe)
			return (0);
		cur = cur->next;
	}
	while(cmd->cmd[i])
	{
		add_env_var(data, cmd->cmd[i]);
		i++;
	}
	return(1);
}

int b_unset(t_data *data, t_cmd *cmd)
{
	int i;
	t_redir *cur;

	i = 1;
	cur = cmd->redirections;
	while(cur)
	{
		fill_fds(cur, data);
		if(data->file[0] == -1 || data->file[1] == -1)
			return(1);
		if(cur->pipe)
			return (0);
		cur = cur->next;
	}
	while(cmd->cmd[i])
	{
		del_env_var(data, cmd->cmd[i]);
		i++;
	}
	return(1);
}
