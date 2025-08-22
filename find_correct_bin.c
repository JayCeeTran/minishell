#include "minishell.h"

int	is_there_slash(char *s);

char *find_bin(t_cmd *cmd, t_data *data)
{
	char *path;
	int fd;

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
				fd = open(cmd->cmd[0], O_WRONLY);
				if(fd > 0)
					close(fd);
				else if(fd == -1 && errno == EISDIR)
				{
					is_dir_error(cmd->cmd[0]);
					close_free_exit(NULL, 126, data, 0);
				}
				path = ft_strdup(cmd->cmd[0]);
				return(path);
			}
			else
			{
				no_permission(cmd->cmd[0]);
				close_free_exit(NULL, 126, data, 0);
			}
		}
		else
		{
			no_such_file(cmd->cmd[0]);
			close_free_exit(NULL, 127, data, 0);
		}
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
			close_free_exit("Error: Malloc Failed!\n", 1, data, 0);	
		path = ft_strjoin(slash, cmd->cmd[0]);
		if(!path)
		{
			free(slash);
			close_free_exit("Error: Malloc Failed!\n", 1, data, 0);
		}
		free(slash);
		if(check_existence_permission(path, data, cmd))
			return(path);
		free(path);
		i++;
	}
	return(NULL);
}

int	is_there_slash(char *s)
{
	int i;

	i = 0;
	while(s[i])
	{
		if(s[i] == '/')
			return(1);
		i++;
	}
	return(0);
}

int check_existence_permission(char *s, t_data *data, t_cmd *cmd)
{
	int fd;

	if(access(s, F_OK) == 0)
	{
		fd = open(s, O_WRONLY);
		if(fd > 1)
			close(fd);
		else if(fd == -1 && errno == EISDIR)
		{	
			is_dir_error(s);
			close_free_exit(NULL, 1, data, 0);
		}
		if(access(s, X_OK) == 0)
			return(1);
		else
		{
			no_permission(cmd->cmd[0]);
			close_free_exit(NULL, 126, data, 0);
		}
	}
	return(0);
}
