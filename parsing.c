/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:36:25 by jtran             #+#    #+#             */
/*   Updated: 2025/08/26 15:36:28 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*create_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->redirs = NULL;
	cmd->pipe = 0;
	cmd->next = NULL;
	cmd->cmd = NULL;
	return (cmd);
}

static t_cmd	*build_single_cmd(t_token **cur)
{
	t_cmd	*cmd;
	t_token	*cur_save;

	cmd = create_cmd();
	if (!cmd)
		return (NULL);
	cur_save = *cur;
	cmd->cmd = fill_cmd_array(cur);
	if (!cmd->cmd)
	{
		free(cmd);
		return (NULL);
	}
	if (fill_redirections(cmd, cur_save, *cur) == -1)
		return (NULL);
	if (*cur && (*cur)->is_op == 1 && !ft_strncmp((*cur)->token, "|", 2))
	{
		cmd->pipe = 1;
		*cur = (*cur)->next;
	}
	return (cmd);
}

t_cmd	*parse_cmd_list(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*last;
	t_cmd	*cur_cmd;
	t_token	*cur;

	if (!tokens)
		return (NULL);
	head = NULL;
	cur = tokens;
	while (cur)
	{
		cur_cmd = build_single_cmd(&cur);
		if (!cur_cmd)
		{
			free_cmd_list(head);
			return (NULL);
		}
		if (!head)
			head = cur_cmd;
		else
			last->next = cur_cmd;
		last = cur_cmd;
	}
	return (head);
}
