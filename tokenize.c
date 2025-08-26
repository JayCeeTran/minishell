#include "minishell.h"

static int	tokenize_space(t_dollar_ctx *ctx)
{
	if (ctx->s[*ctx->i] != ' ')
		return (0);
	if (!append_token(ctx->head, new_tok(" ", 1, 3)))
		return (-1);
	(*ctx->i)++;
	return (1);
}

static int	tokenize_operator(t_dollar_ctx *ctx)
{
	if (!is_op_char(ctx->s[*ctx->i]))
		return (0);
	if (ctx->s[*ctx->i] == '>' && ctx->s[*ctx->i + 1] == ctx->s[*ctx->i])
	{
		if (!append_token(ctx->head, new_tok(&ctx->s[*ctx->i], 2, 1)))
			return (-1);
		*ctx->i += 2;
	}
	else if (ctx->s[*ctx->i] == '<' && ctx->s[*ctx->i + 1] == ctx->s[*ctx->i])
	{
		if (!append_token(ctx->head, new_tok("<<", 2, 1)))
			return (-1);
		ctx->heredoc_mode = 1;
		*ctx->i += 2;
	}
	else
	{
		if (!append_token(ctx->head, new_tok(&ctx->s[*ctx->i], 1, 1)))
			return (-1);
		(*ctx->i)++;
	}
	return (1);
}

static int	tokenize_unquoted_word(t_dollar_ctx *ctx)
{
	int	start;

	start = *ctx->i;
	while (ctx->s[*ctx->i] && ctx->s[*ctx->i] != ' '
		&& !is_op_char(ctx->s[*ctx->i]) && ctx->s[*ctx->i] != '\''
		&& ctx->s[*ctx->i] != '"' && ctx->s[*ctx->i] != '$')
		(*ctx->i)++;
	if (start < *ctx->i)
	{
		if (!append_token(ctx->head, new_tok(&ctx->s[start],
					*ctx->i - start, 0)))
			return (-1);
		else
			return (1);
	}
	return (0);
}

static int	tokenize_step(t_dollar_ctx *ctx)
{
	int	ret;

	ret = tokenize_space(ctx);
	if (ret == -1)
		return (-1);
	if (ret)
		return (1);
	ret = tokenize_operator(ctx);
	if (ret == -1)
		return (-1);
	if (ret)
		return (1);
	ret = tokenize_quotes_or_dollar(ctx);
	if (ret == -1)
		return (-1);
	if (ret)
		return (1);
	if (!tokenize_unquoted_word(ctx))
		return (-1);
	return (1);
}

t_token	*tokenize(char *s)
{
	t_token			*head;
	int				i;
	int				ret;
	t_dollar_ctx	ctx;

	ctx.s = s;
	head = NULL;
	ctx.head = &head;
	i = 0;
	ctx.i = &i;
	ctx.heredoc_mode = 0;
	while (s[i])
	{
		ret = tokenize_step(&ctx);
		if (ret == -1)
		{
			free_token(head);
			return (NULL);
		}
	}
	ctx.heredoc_mode = 0;
	return (*ctx.head);
}
