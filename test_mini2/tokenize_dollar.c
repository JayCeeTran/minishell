/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:30:20 by jtran             #+#    #+#             */
/*   Updated: 2025/08/26 19:30:35 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	tokenize_dollar_pid(t_dollar_ctx *ctx)
{
	(*ctx->i)++;
	if (!append_token(ctx->head, new_tok("$$", 2, ctx->expand)))
		return (-1);
	return (1);
}

static int	tokenize_dollar_quoted(t_dollar_ctx *ctx, int start)
{
	char	q;

	q = ctx->s[(*ctx->i)++];
	while (ctx->s[*ctx->i] && ctx->s[*ctx->i] != q)
		(*ctx->i)++;
	if (ctx->s[*ctx->i] == q)
		(*ctx->i)++;
	if (!append_token(ctx->head, new_tok(&ctx->s[start], *ctx->i - start,
				ctx->expand)))
		return (-1);
	return (1);
}

static int	tokenize_dollar_invalid(t_dollar_ctx *ctx, int start)
{
	if (!append_token(ctx->head, new_tok(&ctx->s[start], 1, 0)))
		return (-1);
	return (1);
}

static int	tokenize_dollar_var(t_dollar_ctx *ctx, int start)
{
	while (ctx->s[*ctx->i] && is_valid_var_char(ctx->s[*ctx->i]))
		(*ctx->i)++;
	if (!append_token(ctx->head, new_tok(&ctx->s[start], *ctx->i - start,
				ctx->expand)))
		return (-1);
	return (1);
}

int	tokenize_dollar(t_dollar_ctx *ctx, int out_single)
{
	int	start;

	start = *ctx->i;
	(*ctx->i)++;
	if (out_single && !ctx->heredoc_mode)
		ctx->expand = 2;
	else
		ctx->expand = 0;
	if (ctx->s[*ctx->i] == '?')
		return (tokenize_dollar_status(ctx, start));
	else if (ctx->s[*ctx->i] == '$')
		return (tokenize_dollar_pid(ctx));
	else if (ctx->s[*ctx->i] == '\'' || ctx->s[*ctx->i] == '"')
		return (tokenize_dollar_quoted(ctx, start));
	else if (!is_valid_var_char(ctx->s[*ctx->i]))
		return (tokenize_dollar_invalid(ctx, start));
	else
		return (tokenize_dollar_var(ctx, start));
}
