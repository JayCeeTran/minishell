#include "minishell.h"

void	children(t_data *data, t_cmd *cmd, t_pipes *pipes)
{
	char *path;
	int flag_pipe;
	t_redir *cur;
	
	flag_pipe = 0;
	cur = cmd->redirections;
	while(cur)
	{
		fill_fds(cur, data);
		if(data->file[0] == -1 || data->file[1] == -1)
			close_free_exit(NULL, 1, data);
		if(cur->pipe)
			flag_pipe = 1;
		cur = cur->next;
	}
	redirections(pipes, data, flag_pipe);
	built_ins(data, cmd->cmd);
	path = find_bin(cmd, data);
	close_pipes_and_files(data->file, pipes->new_p, pipes->cur_p, data->first);
	execve(path, cmd->cmd, data->my_env);
	free_all_exit("Execve failed\n", 1, data);
}


int	infile_permission(char *file, int *data_file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if(fd == -1)
	{
		if(errno == EISDIR)
			is_dir_error(file);
		else if(errno == ENOENT || file[0] == '\0')
			no_such_file(file);
		else if(errno == EACCES)
			no_permission(file);
		else
			perror("Error opening infile");
	}
	if(data_file[0] > 0)
		close(data_file[0]);
	return(fd);
}

int	outfile_permission(char *file, int redir, int *data_file)
{
	int fd;

	if(redir == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if(redir == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if(fd == -1)
	{
		if(errno == EISDIR)
			is_dir_error(file);
		else if(errno == EACCES)
			no_permission(file);
		else if(file[0] == '\0')
			no_such_file(file);
		else
			perror("Error opening outfile\n");
	}
	if(data_file[1] > 0)
		close(data_file[1]);
	return(fd);
}
