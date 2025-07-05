#include "minishell.h"

void	backup_or_restore_stdio(t_data *data, int flag);
void	remove_and_free_heredoc(t_data *data);
void	wait_children(t_data *data, pid_t pid);

void	read_list(t_data *data)
{
	t_cmd *cur;
	t_pipes pipes;
	pid_t pid;
	t_heredoc heredoc;

	cur = initialize_data(data, &pipes, &heredoc);
	if(pipe(data->pipe1) == -1)
		free_all_exit("Error\nCreating pipe failed\n", 1, data, 1);
	backup_or_restore_stdio(data, 1);
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
	}
	backup_or_restore_stdio(data, 0);
	close_pipes_and_files(data, data->first - 1);
	free_list(data); 	//data first to keep track if we have second pipe piped
	if(data->first > 1)
		wait_children(data, pid);	//expecting new cmd waiting for prompt
	remove_and_free_heredoc(data);
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

void	unlink_heredocs(t_heredoc *heredoc)
{
	int i;

	i = 0;
	while(i < heredoc->count)
	{
		unlink(heredoc->path[i]);
		i++;
	}
	heredoc->count = 0;
}

void	remove_and_free_heredoc(t_data *data)
{
	unlink_heredocs(data->heredoc);
	free_heredoc_paths(data->heredoc);
	data->heredoc = NULL;
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
