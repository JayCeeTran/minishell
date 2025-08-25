#include "minishell.h"

void	strerror_msg(char *s);
void	signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}


void	children(t_data *data, t_cmd *cmd, t_pipes *pipes)
{
	char *path;
	int flag_pipe;
	t_redir *cur;
	
	flag_pipe = 0;
	path = NULL;
	cur = cmd->redirections;
	if(cmd->pipe)
		flag_pipe = 1;
	while(cur)
	{
		fill_fds(cur, data);
		if(data->file[0] == -1 || data->file[1] == -1)
			close_free_exit(NULL, 1, data, 0);
		cur = cur->next;
	}
	redirections(pipes, data, flag_pipe);
	if(!built_ins(data, cmd))
		path = find_bin(cmd, data);
	close_pipes_and_files(data, data->first);
	if(!path)
		free_all_exit(NULL, 0, data, 0);
	signals();
	execve(path, cmd->cmd, data->my_env);
	free_all_exit("Execve failed\n", 1, data, 0);
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
			strerror_msg(file);
	}
	if(data_file[0] > 0)
		close(data_file[0]);
	return(fd);
}

int	outfile_permission(char *file, int redir, int *data_file)
{
	int fd;
	
	fd = 0;
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
			strerror_msg(file);
	}
	if(data_file[1] > 0)
		close(data_file[1]);
	return(fd);
}

void	strerror_msg(char *s)
{
	write_bash();
	ft_putstr_fd(s, 2);
	write(2, ": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	write(2, "\n", 2);
}
