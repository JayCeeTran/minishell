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

void close_pipes_and_files(int *fd, int *npipe, int *cpipe, int first)
{
	close_fds(fd);
	close_fds(cpipe);
	if(first > 1)
		close_fds(npipe);
}
