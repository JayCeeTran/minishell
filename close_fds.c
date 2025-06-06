#include "minishell.h"

void	close_fds(int *fd)
{
	if(fd)
	{
		if(fd[0] > 0)
			close(fd[0]);
		if(fd[1] > 0)
			close(fd[1]);
	}
}

void close_pipes_and_files(t_data *data, int first)
{
	close_fds(data->file);
	close_fds(data->pipe1);
	close(data->o_stdin);
	close(data->o_stdout);
	if(first > 1)
		close_fds(data->pipe2);
}
