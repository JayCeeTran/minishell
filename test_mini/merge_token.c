/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:27:12 by jtran             #+#    #+#             */
/*   Updated: 2025/08/26 19:27:14 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	merge_tokens(t_token *head)
{
	t_token	*cur;
	t_token	*tmp;

	cur = head;
	while (cur && cur->next)
	{
		if ((cur->is_op != 1 && cur->is_op != 3) && (cur->next->is_op != 1
				&& cur->next->is_op != 3))
		{
			if (cur->is_op == 4 || cur->next->is_op == 4)
				cur->is_op = 4;
			cur->token = ft_strjoin_free(cur->token, cur->next->token);
			if (!cur->token)
				return (-1);
			tmp = cur->next;
			cur->next = tmp->next;
			free(tmp->token);
			free(tmp);
			continue ;
		}
		cur = cur->next;
	}
	return (1);
}

static void	remove_space(t_token **head)
{
	t_token	*cur;
	t_token	*prev;
	t_token	*tmp;

	cur = *head;
	prev = NULL;
	while (cur)
	{
		if (cur->is_op == 3 && ft_strncmp(cur->token, " ", 2) == 0)
		{
			tmp = cur;
			if (prev)
				prev->next = cur->next;
			else
				*head = cur->next;
			cur = cur->next;
			free(tmp->token);
			free(tmp);
			continue ;
		}
		prev = cur;
		cur = cur->next;
	}
}

void	simplify_tokens(t_token **head)
{
	if (!head)
		return ;
	if (merge_tokens(*head) == -1)
	{
		free_token(*head);
		head = NULL;
		return ;
	}
	remove_space(head);
}
