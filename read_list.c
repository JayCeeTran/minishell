#include "minishell.h"

void	backup_stdio(t_data *data);
void	restore_stdio(t_data *data);
void	remove_and_free_heredoc(t_data *data);
void	wait_children(t_data *data, pid_t pid);

void	read_list(t_data *data)
{
	t_cmd *cur;
	t_pipes pipes;
	pid_t pid;

	cur = initialize_data(data, &pipes);
	if(pipe(data->pipe1) == -1)
		free_all_exit("Error\nCreating pipe failed\n", 1, data);
	backup_stdio(data);
	while(cur)
	{
		check_heredoc(cur->redirections, data);
		if(data->first == 1 && built_ins_parent(data, cur))
			break;
		swap_pipes(&pipes, data->first);
		new_pipes(&pipes, data);
		pid = fork();
		fork_helper(pid, data, cur, &pipes);
		cur = cur->next;	
		data->first++;
		remove_and_free_heredoc(data);
	}
	restore_stdio(data);
	close_pipes_and_files(data, data->first - 1);
	free_list(data) 	//data first to keep track if we have second pipe piped
	if(data->first > 1)
		wait_children(data, pid);	//expecting new cmd waiting for prompt
}

void	backup_stdio(t_data *data)
{
	data->o_stdin = dup(0);
	data->o_stdout = dup(1);	
}

void	restore_stdio(t_data *data)
{
	dup2(data->o_stdin, 0);
	dup2(data->o_stdout, 1);
}

void	remove_and_free_heredoc(t_data *data)
{
	if(data->heredoc_path)
	{
		unlink(data->heredoc_path);
		free(data->heredoc_path);
		data->heredoc_path = NULL;
		write(2, "taal eka\n", 9);
	}
}

void	wait_children(t_data *data, pid_t pid)
{
	while(--data->first)
	{
		if(data->first == 1)
		{
			waitpid(pid, &data->status, 0);
			break;
		}
		wait(NULL);
	}
}

/*char *find_bin(t_cmd *cmd, t_data *data)
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
}*/
