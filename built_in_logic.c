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
		if(ft_strcmp(cmd->cmd[0], built_ins[i].name) == 0)
		{
			if(built_ins[i].func(data, cmd, 0))
				close_free_exit(NULL, 0, data, 0);
			else
				close_free_exit(NULL, 1, data, 0);
		}
		i++;
	}
	return(0);
}

int		built_ins_parent(t_data *data, t_cmd *cmd)
{
	//t_redir *cur;
	int i;
	t_built_ins built_ins[20];
	
	if(cmd->pipe)
			return(0);
	initialize_struct(built_ins);
	i = 0;
//	cur = cmd->redirections;
	while(built_ins[i].name)
	{
		if(ft_strcmp(cmd->cmd[0], built_ins[i].name) == 0)
		{
			if(!file_permission_loop(data, cmd->redirections))
			{
				redirections(data->pipe_pointers, data, 0);
				if(built_ins[i].func(data, cmd, 1))
					data->status = 0; //check if this is right place and right code
			}
			return(1);
		}
		i++;
	}
	return(0);
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
