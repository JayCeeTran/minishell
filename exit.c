#include "minishell.h"

int b_exit(t_data *data, t_cmd *cmd)
{
	t_redir *cur;

	cur = cmd->redirections;
	while(cur)
	{
		fill_fds(cur, data);
		if(data->file[0] == -1 || data->file[1] == -1)
			return(0);
		if(cur->pipe)
			return(0);
		cur = cur->next;
	}
	close_pipes_and_files(data->file, data->pipe2, data->pipe1, data->first);
	free_all_exit(NULL, 0, data);
	return(1);
}	
