/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_sub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:36:19 by jtran             #+#    #+#             */
/*   Updated: 2025/08/26 16:16:18 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redir_op(const char *s)
{
	if (!ft_strncmp(s, "<", 2) || !ft_strncmp(s, ">", 2) || !ft_strncmp(s, "<<",
			3) || !ft_strncmp(s, ">>", 3))
		return (1);
	return (0);
}

static int	add_redir(t_redir **head, char *redir, char *file, int expand)
{
	t_redir	*new;
	t_redir	*tmp;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (-1);
	new->expand = expand;
	new->redir = ft_strdup(redir);
	new->file = ft_strdup(file);
	if (!new->redir || !new->file)
		return (free(new->redir), free(new->file), free(new), -1);
	new->next = NULL;
	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (1);
}

static int	count_cmd_words(t_token *cur)
{
	int	count;

	count = 0;
	while (cur && (cur->is_op != 1 || is_redir_op(cur->token))
		&& ft_strncmp(cur->token, "|", 2) != 0)
	{
		if (cur->is_op != 1 || !is_redir_op(cur->token))
			count++;
		if (cur->is_op == 1 && is_redir_op(cur->token))
			cur = cur->next;
		cur = cur->next;
	}
	return (count);
}

int	fill_redirections(t_cmd *cmd, t_token *start, t_token *end)
{
	t_token	*tmp;

	tmp = start;
	while (tmp && tmp != end)
	{
		if (tmp->is_op == 1 && is_redir_op(tmp->token) && tmp->next
			&& tmp->next->is_op != 1)
		{
			if (!ft_strncmp(tmp->token, "<<", 3) && tmp->next->is_op == 4)
			{
				if (add_redir(&cmd->redirs, tmp->token, tmp->next->token, 1)
					== -1)
					return (-1);
			}
			else if (add_redir(&cmd->redirs, tmp->token, tmp->next->token, 0)
				== -1)
				return (-1);
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	return (1);
}

char	**fill_cmd_array(t_token **cur)
{
	int		i;
	int		count;
	char	**cmd;

	count = count_cmd_words(*cur);
	cmd = ft_calloc(count + 1, sizeof(char *));
	if (!cmd)
		return (NULL);
	i = 0;
	while (*cur && !((*cur)->is_op == 1 && !ft_strncmp((*cur)->token, "|", 2)))
	{
		if ((*cur)->is_op == 1 && is_redir_op((*cur)->token) && (*cur)->next)
			*cur = (*cur)->next;
		else
		{
			cmd[i] = ft_strdup((*cur)->token);
			if (!cmd[i])
				return (NULL);
			i++;
		}
		*cur = (*cur)->next;
	}
	cmd[i] = NULL;
	return (cmd);
}
