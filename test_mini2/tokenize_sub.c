/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_sub.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 10:44:26 by hoale             #+#    #+#             */
/*   Updated: 2025/08/26 19:32:44 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_op_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

t_token	*new_tok(const char *s, size_t len, int is_op)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->token = ft_substr(s, 0, len);
	if (!node->token)
	{
		free(node);
		return (NULL);
	}
	node->is_op = is_op;
	node->next = NULL;
	return (node);
}

int	append_token(t_token **head, t_token *node)
{
	t_token	*tmp;

	if (!node)
		return (0);
	if (!*head)
	{
		*head = node;
		return (1);
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	return (1);
}

int	tokenize_dollar_status(t_dollar_ctx *ctx, int start)
{
	(*ctx->i)++;
	if (!append_token(ctx->head, new_tok(&ctx->s[start], *ctx->i - start,
				ctx->expand)))
		return (-1);
	return (1);
}

int	is_empty_segment(t_token *start, t_token *end)
{
	t_token	*tmp;

	tmp = start;
	while (tmp && tmp != end)
	{
		if (tmp->is_op != 3)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
