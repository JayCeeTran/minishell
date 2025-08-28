/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:25:53 by jtran             #+#    #+#             */
/*   Updated: 2025/08/26 19:48:13 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd *cmd)
{
	int		i;
	t_redir	*tmp;

	if (!cmd)
		return ;
	if (cmd->cmd)
	{
		i = 0;
		while (cmd->cmd[i])
			free(cmd->cmd[i++]);
		free(cmd->cmd);
	}
	while (cmd->redirs)
	{
		tmp = cmd->redirs;
		cmd->redirs = cmd->redirs->next;
		free(tmp->redir);
		free(tmp->file);
		free(tmp);
	}
	free(cmd);
}

void	free_cmd_list(t_cmd *head)
{
	t_cmd	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free_cmd(tmp);
	}
}

void	free_split_exit(char **cmd)
{
	free_split(cmd);
	err_msg_exit("Error\nReparsing failed\n", 1);
}

void	free_heredoc_paths(t_heredoc *heredoc)
{
	int	i;

	i = 0;
	while (i < heredoc->count)
	{
		free(heredoc->path[i]);
		i++;
	}
}

void	free_all_exit(char *s, int excode, t_data *data, int parent)
{
	if(data->path)
		free_split(data->path);
	if(data->my_env)
		free_split(data->my_env);
	if(data->export_list)
		free_split(data->export_list);
	if (data->list)
		free_cmd_list(data->list);
	if (parent)
		unlink("heredoc");
	if (excode == -1)
		exit(WEXITSTATUS(data->status));
	err_msg_exit(s, excode);
}
