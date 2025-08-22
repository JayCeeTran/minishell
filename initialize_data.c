#include "minishell.h"

t_cmd	*initialize_data(t_data *data, t_pipes *pipes, t_heredoc *h_doc)
{
	data->file[0] = 0;
	data->file[1] = 0;
	data->first = 1;
	//data->status = 0;
	h_doc->count = 0;
	data->heredoc = h_doc;
	data->pipe_pointers = pipes;
	pipes->cur_p = data->pipe1;
	pipes->new_p = data->pipe2;
	return(data->list);
}

void	fill_fds(t_redir *redir, t_data *data)
{
	t_redir *cur;

	cur = redir;
	if(cur->redir && cur->file)
	{
		if(ft_strcmp(cur->redir, "<") == 0)	
			data->file[0] = infile_permission(cur->file, data->file);
		else if(ft_strcmp(cur->redir, ">") == 0)
			data->file[1] = outfile_permission(cur->file, 1, data->file);
		else if(ft_strcmp(cur->redir, ">>") == 0)
			data->file[1] = outfile_permission(cur->file, 2, data->file);
		else if(ft_strcmp(cur->redir, "<<") == 0)
		{
			if(data->file[0] > 0)
				close(data->file[0]);
			data->file[0] = open(data->heredoc->path[data->heredoc->count - 1], O_RDONLY);
		}
	}
}

void	redirections(t_pipes *pipes, t_data *data, int flag)
{
	if(data->first != 1)
		dup2(pipes->cur_p[0], 0); 
	if(flag && data->first != 1)
		dup2(pipes->new_p[1], 1);
	else if(flag && data->first == 1)
		dup2(pipes->cur_p[1], 1);
	if(data->file[0] > 0)
		dup2(data->file[0], 0);
	if(data->file[1] > 0)
		dup2(data->file[1], 1);
}
