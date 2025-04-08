#include "minishell.h"

void	swap_pipes(t_pipes *pipes, int first)
{
	if(first > 2)
	{
		close_fds(pipes->cur_p);
		pipes->temp_p = pipes->cur_p;
		pipes->cur_p = pipes->new_p;
		pipes->new_p = pipes->temp_p;
	}
}

void	new_pipes(t_pipes *pipes, t_data *data)
{
	if(data->first > 1)
	{
		if(pipe(pipes->new_p) == -1)
		{
			close_fds(pipes->cur_p);
			close_fds(data->file);
			free_all_exit("Error\nCreating pipe failed\n", 1, data);
		}
	}
}

void	fork_helper(pid_t pid, t_data *data, t_cmd *cur, t_pipes *pipes)
{
	if(pid == -1)
	{
		close_pipes_and_files(data->file, pipes->new_p, pipes->cur_p, data->first);
		free_all_exit("Error\nFork Failed\n", 1, data);
	}
	if(pid == 0)
		children(data, cur, pipes);
}
