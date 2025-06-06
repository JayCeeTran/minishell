#include "minishell.h"

int	b_echo(t_data *data, t_cmd *cmd)
{
	int i;
	int nl;

	i = 1;
	nl = 1;
	(void)data;
	if(cmd->cmd[1] && ft_strcmp(cmd->cmd[1], "-n") == 0)
	{
		nl = 0;
		i++;
	}
	while(cmd->cmd[i])
	{
		ft_putstr_fd(cmd->cmd[i], 1);
		if(cmd->cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if(nl)
		write(1, "\n", 1);
	return(1);
}

int	b_pwd(t_data *data, t_cmd *cmd)
{
	char *pwd;

	(void)cmd;
	pwd = getenv("PWD");
	if(!pwd)
	{
		close_pipes_and_files(data, data->first);
		free_all_exit("Failed to get pwd\n", 1, data);
	}
	ft_putstr_fd(pwd, 1);
	write(1, "\n", 1);
	return(1);
}

int	b_env(t_data *data, t_cmd *cmd)
{
	int i;

	i = 0;
	(void)cmd;
	while(data->env[i])
	{
		ft_putstr_fd(data->env[i], 1);
		write(1, "\n", 1);
		i++;
	}
	return(1);
}

int b_exit(t_data *data, t_cmd *cmd)
{
	(void)cmd;
	close_pipes_and_files(data, data->first);
	free_all_exit(NULL, 0, data);
	return(1);
}
