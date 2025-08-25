#include "minishell.h"

void	error_msg_exit(int permission, t_data *data, t_cmd *cmd)
{
	if(permission)
	{	
		no_permission(cmd->cmd[0]);
		close_free_exit(NULL, 126, data, 0);
	}
	else
	{
		no_such_file(cmd->cmd[0]);
		close_free_exit(NULL, 127, data, 0);
	}
}

char *dup_path(t_cmd *cmd, t_data *data)
{
	char *path;

	path = ft_strdup(cmd->cmd[0]);
	if(!path)
		close_free_exit("Error: Malloc Failed!\n", 1, data, 0);
	return(path);
}

void	check_if_cmd_is_dir(t_data *data, t_cmd *cmd)
{
	int fd;

	fd = open(cmd->cmd[0], O_WRONLY);
	if(fd > 0)
		close(fd);
	else if(fd == -1 && errno == EISDIR)
	{
		is_dir_error(cmd->cmd[0]);
		close_free_exit(NULL, 126, data, 0);
	}
}

char	*return_path_or_exit(t_data *data, t_cmd *cmd)
{
	char *path;
	
	path = append_to_path(cmd, data);
	if(!path)	
		command_not_found(cmd, data);
	return(path);
}

char *find_bin(t_cmd *cmd, t_data *data)
{
	if(!cmd->cmd || !cmd->cmd[0]) //check function return if theres something to be done
		return(NULL);
	if(cmd->cmd[0][0] == '\0')
		close_free_exit("'': command not found\n", 127, data, 0);
	if(is_there_slash(cmd->cmd[0]))
	{
		if(access(cmd->cmd[0], F_OK) == 0)
		{
			if(access(cmd->cmd[0], X_OK) == 0)
			{
				check_if_cmd_is_dir(data, cmd);
				return(ft_strdup(cmd->cmd[0]));
			}
			else
				error_msg_exit(1, data, cmd);
		}
		else
			error_msg_exit(0, data, cmd);
	}
	return(return_path_or_exit(data, cmd));
}
