#include "minishell.h"

void	built_ins(t_data *data, char **cmd)
{
	int i;

	i = 1;
	if(ft_strcmp(cmd[0], "echo") == 0)
		b_echo(data, cmd);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		b_pwd(data);
	else if(ft_strcmp(cmd[0], "env") == 0)
		b_env(data);
	else if(ft_strcmp(cmd[0], "export") == 0)
	{
		while(cmd[i])
			add_env_var(data, cmd[i++]);
	}
	else if(ft_strcmp(cmd[0], "unset") == 0)
	{
		while(cmd[i])
			del_env_var(data, cmd[i++]);
	}
	else if(ft_strcmp(cmd[0], "exit") == 0)
	{
		close_pipes_and_files(data->file, data->pipe2, data->pipe1, data->first);
		free_all_exit(NULL, 0, data);
	}
	 //if no commands found might not need to exit
	//close_pipes_and_files(data->file, data->pipe2, data->pipe1, data->first);
	//free_all_exit("", 0, data);
}

int		built_ins_parent(t_data *data, t_cmd *cmd)
{
	char **com;

	com = cmd->cmd;
	if(ft_strcmp(com[0], "export") == 0)
	{	
		if(b_export(data, cmd))
			return(1);
	}
	else if(ft_strcmp(com[0], "unset") == 0)
	{
		if(b_unset(data, cmd))
			return(1);
	}
	else if(ft_strcmp(com[0], "exit") == 0)
	{
		if(b_exit(data, cmd))
			return(1);
	}
	else if(ft_strcmp(com[0], "cd") == 0)
	{
		if(b_cd(data, cmd))
			return(1);
	}
	return(0);
}
