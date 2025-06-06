#include "minishell.h"

char *find_bin(t_cmd *cmd, t_data *data)
{
	char *path;
	int fd;

	if(!cmd->cmd || !cmd->cmd[0]) //check function return if theres something to be done
		return(NULL);
	if((cmd->cmd[0][0] == '/' || cmd->cmd[0][0] == '.') && access(cmd->cmd[0], F_OK) == 0)
	{
		if(access(cmd->cmd[0], X_OK) == 0)
		{
			fd = open(cmd->cmd[0], O_WRONLY);
			if(fd > 0)
				close(fd);
			else if(fd == -1 && errno == EISDIR)
			{
				is_dir_error(cmd->cmd[0]);
				close_free_exit(NULL, 1, data);
			}
			path = ft_strdup(cmd->cmd[0]);
			return(path);
		}
		else
		{
			no_permission(cmd->cmd[0]);
			close_free_exit(NULL, 126, data);
		}
	}
	if(cmd->cmd[0][0] == '/' || cmd->cmd[0][0] == '.')
	{
		no_such_file(cmd->cmd[0]);
		close_free_exit(NULL, 1, data);
	}
	path = append_to_path(cmd, data);
	if(!path)
		command_not_found(cmd, data);
	return(path);
}

char *append_to_path(t_cmd *cmd, t_data *data)
{
	int i;
	char *path;
	char *slash;

	i = 0;
	while(data->path[i])
	{
		slash = ft_strjoin(data->path[i], "/");
		if(!slash)
			close_free_exit("Error\nMalloc Failed\n", 1, data);	
		path = ft_strjoin(slash, cmd->cmd[0]);
		if(!path)
		{
			free(slash);
			close_free_exit("Error\nMalloc Failed\n", 1, data);
		}
		free(slash);
		if(check_existence_permission(path, data, cmd))
			return(path);
		free(path);
		i++;
	}
	return(NULL);
}

int check_existence_permission(char *s, t_data *data, t_cmd *cmd)
{
	if(access(s, F_OK) == 0)
	{
		if(access(s, X_OK) == 0)
			return(1);
		else
		{
			no_permission(cmd->cmd[0]);
			close_free_exit(NULL, 126, data);
		}
	}
	return(0);
}
