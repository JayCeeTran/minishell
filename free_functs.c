#include "minishell.h"

void	free_split(char **split)
{
	int i;

	i = 0;
	while(split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_split_exit(char **cmd)
{
	free_split(cmd);
	err_msg_exit("Error\nReparsing failed\n", 1);
}

void	free_all_exit(char *s, int excode, t_data *data)
{
	free_split(data->path);
	free_split(data->my_env);
	free_list(data);
	if(data->heredoc_path)
	{
		free(data->heredoc_path);
		data->heredoc_path = NULL;
		write(2, "taal on kayty\n", 13);
	}
	if(excode == -1)
		exit(WEXITSTATUS(data->status)); //MAYBE ANOTHER PLACE!!
	err_msg_exit(s, excode);
}

void	free_list(t_data *data)
{
	t_cmd *cur;

	while(data->list)
	{	
		cur = data->list;
		data->list = data->list->next;
		free_split(cur->cmd);
		free_redir(cur->redirections);
		free(cur);
	}
	data->list = NULL;
}

void	free_redir(t_redir *directs)
{
	t_redir *cur;

	while(directs)
	{
		cur = directs;
		directs = directs->next;
		free(cur->redir);
		free(cur->file);
		free(cur);
	}
}
