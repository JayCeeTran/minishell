#include "minishell.h"

void	backup_or_restore_stdio(t_data *data, int flag);
void	wait_children(t_data *data, pid_t pid);

pid_t	swap_create_pipes_fork(t_data *data, t_pipes *pipes, t_cmd *cmd)
{
	pid_t pid;

	swap_pipes(pipes, data->first);
	new_pipes(pipes, data);
	pid = fork();
	fork_helper(pid, data, cmd, pipes);
	return(pid);
}

void	read_list(t_data *data)
{
	t_cmd *cur;
	t_pipes pipes;
	pid_t pid;

	cur = initialize_data(data, &pipes);
	if(pipe(data->pipe1) == -1)
		free_all_exit("Error\nCreating pipe failed\n", 1, data, 1);
	backup_or_restore_stdio(data, 1);
	while(cur)
	{
		if(fork_heredoc(data, cur))
			break;
		if(data->first == 1 && built_ins_parent(data, cur))
			break;
		pid = swap_create_pipes_fork(data, &pipes, cur);
		cur = cur->next;	
		data->first++;
	}
	backup_or_restore_stdio(data, 0);
	close_pipes_and_files(data, data->first - 1);
	free_list(data); 	
	if(data->first > 1)
		wait_children(data, pid);
	unlink("heredoc");
}

void	backup_or_restore_stdio(t_data *data, int flag)
{
	if(flag)
	{
		data->o_stdin = dup(0);
		data->o_stdout = dup(1);
	}
	else
	{
		dup2(data->o_stdin, 0);
		dup2(data->o_stdout, 1);
	}
}

void	wait_children(t_data *data, pid_t pid)
{
	int status;
	pid_t cur_pid;
	int signal;

	while(--data->first)
	{
		cur_pid = wait(&status);
		if(pid == cur_pid)
		{
			if(WIFSIGNALED(status))
			{
				signal = WTERMSIG(status);
				data->status = 128 + signal;
				if(signal == SIGQUIT)
					ft_putstr_fd("Quit (core dumped)\n", 2);
				else if(signal == SIGINT)
					ft_putstr_fd("\n", 2);
			}
			else 
				data->status = WEXITSTATUS(status);

		}
	}
}
