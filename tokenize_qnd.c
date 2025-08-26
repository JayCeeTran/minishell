/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_qnd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:36:55 by jtran             #+#    #+#             */
/*   Updated: 2025/08/26 15:36:58 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_dq_dollar(t_dollar_ctx *ctx, int *start)
{
	if (*start < *ctx->i)
	{
		if (!append_token(ctx->head, new_tok(&ctx->s[*start], *ctx->i - *start,
					0)))
			return (-1);
	}
	if (tokenize_dollar(ctx, 1) == -1)
		return (-1);
	*start = *ctx->i;
	return (1);
}

static int	finalize_dq_segment(t_dollar_ctx *ctx, int start)
{
	if (start < *ctx->i)
	{
		if (!append_token(ctx->head, new_tok(&ctx->s[start], *ctx->i - start,
					4)))
			return (-1);
	}
	else if (ctx->s[*ctx->i] == '"')
	{
		if (!append_token(ctx->head, new_tok("", 0, 4)))
			return (-1);
	}
	if (ctx->s[*ctx->i] == '"')
		(*ctx->i)++;
	return (1);
}

int	tokenize_double_quote(t_dollar_ctx *ctx)
{
	int	start;

	(*ctx->i)++;
	start = *ctx->i;
	while (ctx->s[*ctx->i] && ctx->s[*ctx->i] != '"')
	{
		if (ctx->s[*ctx->i] == '$')
		{
			if (handle_dq_dollar(ctx, &start) == -1)
				return (-1);
			continue ;
		}
		(*ctx->i)++;
	}
	return (finalize_dq_segment(ctx, start));
}

static int	tokenize_single_quote(t_dollar_ctx *ctx)
{
	int	start;

	(*ctx->i)++;
	start = *ctx->i;
	while (ctx->s[*ctx->i] && ctx->s[*ctx->i] != '\'')
		(*ctx->i)++;
	if (start < *ctx->i)
	{
		if (!append_token(ctx->head, new_tok(&ctx->s[start], *ctx->i - start,
					0)))
			return (-1);
	}
	else if (ctx->s[*ctx->i] == '\'')
	{
		if (!append_token(ctx->head, new_tok("", 0, 0)))
			return (-1);
	}
	if (ctx->s[*ctx->i] == '\'')
		(*ctx->i)++;
	return (1);
}

int	tokenize_quotes_or_dollar(t_dollar_ctx *ctx)
{
	if (ctx->s[*ctx->i] == '"')
		return (tokenize_double_quote(ctx));
	if (ctx->s[*ctx->i] == '\'')
		return (tokenize_single_quote(ctx));
	if (ctx->s[*ctx->i] == '$')
		return (tokenize_dollar(ctx, 1));
	return (0);
}
