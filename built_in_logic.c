#include "minishell.h"

int	file_permission_loop(t_data *data, t_redir *cur);

int	built_ins(t_data *data, t_cmd *cmd)
{
	int i;
	t_built_ins built_ins[20];
	
	initialize_struct(built_ins);
	i = 0;
	while(built_ins[i].name)
	{
		if(ft_strcmp(cmd->cmd[0], built_ins[i].name) == 0 && built_ins[i].func(data, cmd))
		{
			close_pipes_and_files(data, data->first);
			free_all_exit(NULL, 0, data);
		}
		i++;
	}
/*	if(ft_strcmp(cmd[0], "echo") == 0)
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
		(void)i;
	else
		return(0);
*/	return(0);
}

int		built_ins_parent(t_data *data, t_cmd *cmd)
{
	t_redir *cur;
	int i;
	t_built_ins built_ins[20];
	
	initialize_struct(built_ins);
	i = 0;
	cur = cmd->redirections;
	while(cur)
	{
		if(cur->pipe)
			return(0);
		cur = cur->next;
	}
	while(built_ins[i].name)
	{
		if(ft_strcmp(cmd->cmd[0], built_ins[i].name) == 0)
		{
			if(!file_permission_loop(data, cmd->redirections))
			{
				redirections(data->pipe_pointers, data, 0);
				built_ins[i].func(data, cmd);
			}
			return(1);
		}
		i++;
	}
/*	if((ft_strcmp(cmd->cmd[0], "export") == 0 && b_export(data, cmd, 0)) || 
	(ft_strcmp(cmd->cmd[0], "unset") == 0 && b_unset(data, cmd, 0)) ||
	(ft_strcmp(cmd->cmd[0], "exit") == 0 && b_exit(data, cmd, 0)) ||
	(ft_strcmp(cmd->cmd[0], "cd") == 0 && b_cd(data, cmd, 0)))
		return(1);
*/	return(0);
}

int	file_permission_loop(t_data *data, t_redir *cur)
{
	while(cur)
        {
                fill_fds(cur, data);
                if(data->file[0] == -1 || data->file[1] == -1)
		{
			data->status = 1; //change so $? can expand to correct exit code;
                        return(1);
		}
                cur = cur->next;
        }
	return(0);
}
