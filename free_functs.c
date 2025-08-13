#include "minishell.h"

void	free_split(char **split)
{
	int i;

	i = 0;
	if(!split)
		return;
	while(split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_split_index(char **split, int n)
{
	int i;

	i = 0;
	if(!split)
		return;
	while(i < n)
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

void	free_heredoc_paths(t_heredoc *heredoc)
{
	int i;

	i = 0;
	while(i < heredoc->count)
	{
		free(heredoc->path[i]);
		i++;
	}
}

void	free_all_exit(char *s, int excode, t_data *data, int parent)
{
	free_split(data->path);
	free_split(data->my_env);
	free_list(data);
	if(data->heredoc)
		free_heredoc_paths(data->heredoc);
	if(data->heredoc && parent)
		unlink_heredocs(data->heredoc);
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

void	free_token(t_token *token)
{
	t_token *temp;
	while(token)
	{
		temp = token;
		token = token->next;
		free(temp->token);
		free(temp);
	}
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
