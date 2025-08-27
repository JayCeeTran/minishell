/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:29:25 by jtran             #+#    #+#             */
/*   Updated: 2025/08/27 17:48:40 by jtran            ###   ########.fr       */
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

static t_cmd	*build_single_cmd(t_token **cur, t_data *data, t_token *tokens)
{
	t_cmd	*cmd;
	t_token	*cur_save;

	cmd = create_cmd();
	if (!cmd)
		free_tokens_all_exit("Malloc failed!\n", tokens, data);;
	cur_save = *cur;
	cmd->cmd = fill_cmd_array(cur, data, tokens);
	if (fill_redirections(cmd, cur_save, *cur) == -1)
		free_tokens_all_exit("Malloc failed!\n", tokens, data);
	if (*cur && (*cur)->is_op == 1 && !ft_strncmp((*cur)->token, "|", 2))
	{
		cmd->pipe = 1;
		*cur = (*cur)->next;
	}
	return (cmd);
}

t_cmd	*parse_cmd_list(t_token *tokens, t_data *data)
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
		cur_cmd = build_single_cmd(&cur, data, tokens);
		if (!head)
			head = cur_cmd;
		else
			last->next = cur_cmd;
		last = cur_cmd;
	}
	return (head);
}
