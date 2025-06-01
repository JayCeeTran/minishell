#include "minishell.h"

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

void	check_heredoc(t_redir *dir, t_data *data)
{
	char *input;
	char *limit;
	int	fd;
	int i;

	i = 0;
	while(dir)
	{
		if(dir->file && dir->redir)
		{
			if(ft_strcmp(dir->redir, "<<") == 0)
			{
				i++;
				limit = dir->file;
				fd = open("heredoccc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if(fd == -1)
					close_free_exit("Heredoc opening failed\n", 1, data);
				while(1)
				{
					input = readline("> ");
					if(ft_strcmp(input, limit) == 0)
						break;
					ft_putstr_fd(input, fd);
					write(fd, "\n", 1);
					free(input);
				}
				close(fd);
			}
		}
		if(i == 17)
			close_free_exit("-bash: maximum here-document count exceeded\n", 1, data);
		dir = dir->next;	//17 heredoccc + >, <, not tested
	}
}

void	read_list(t_data *data)
{
	t_cmd *cur;
	t_pipes pipes;
	pid_t pid;

	cur = initialize_data(data, &pipes);
	if(pipe(data->pipe1) == -1)
		free_all_exit("Error\nCreating pipe failed\n", 1, data);
	while(cur)
	{
		check_heredoc(cur->redirections, data);
		if(built_ins_parent(data, cur))
			break;
		swap_pipes(&pipes, data->first);
		new_pipes(&pipes, data);
		pid = fork();
		fork_helper(pid, data, cur, &pipes);
		cur = cur->next;	
		data->first++;
	}
	close_pipes_and_files(data->file, data->pipe2, data->pipe1, data->first - 1); 
	//data first to keep track if we have second pipe piped
	wait_children(data, pid);
	//expecting new cmd waiting for prompt
}

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
