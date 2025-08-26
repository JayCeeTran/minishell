/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:09:06 by jtran             #+#    #+#             */
/*   Updated: 2025/08/26 16:12:11 by jtran            ###   ########.fr       */
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
