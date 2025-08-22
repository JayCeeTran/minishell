#include "minishell.h"

int	is_op_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static t_token	*new_token_str(const char *s, size_t len, int is_op)
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
	node->is_operator = is_op;
	node->next = NULL;
	return (node);
}

static void	append_token(t_token **head, t_token *node)
{
	t_token *tmp;

	if (!node)
		return ;
	if (!*head)
	{
		*head = node;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

/* handle $<quote> or $VAR starting at s[*i] where s[*i] == '$' */
/* outside_single indicates whether expansion is allowed (if 0 -> inside single quotes) */
static void	handle_dollar(const char *s, int *i, t_token **head, int outside_single)
{
	int	start;
	int	expand;

	start = *i;           /* '$' position */
	(*i)++;               /* skip '$' */
	expand = outside_single ? 2 : 0;

	/* $'VAR' or $"VAR" */
	if (s[*i] == '\'' || s[*i] == '"')
	{
		char q = s[(*i)++];
		while (s[*i] && s[*i] != q)
			(*i)++;
		if (s[*i] == q)
			(*i)++; /* skip closing quote if present */
		/* Safe: *i is now at \0 or after quote */
		append_token(head, new_token_str(&s[start], *i - start, expand));
		return;
	}

	/* normal $VAR */
	if (!is_valid_var_char(s[*i]))
	{
		/* nothing valid after $, treat $ as literal */
		append_token(head, new_token_str(&s[start], 1, 0));
		return;
	}

	while (s[*i] && is_valid_var_char(s[*i]))
		(*i)++;
	append_token(head, new_token_str(&s[start], *i - start, expand));
}

/* handle "double quoted" section: produce token(s) for plain segments and $VAR inside */
static void	handle_double_quote(const char *s, int *i, t_token **head)
{
	int	seg_start;

	/* skip opening " */
	(*i)++;
	seg_start = *i;
	while (s[*i] && s[*i] != '"')
	{
		if (s[*i] == '$')
		{
			/* flush preceding plain text inside the double quotes */
			if (seg_start < *i)
				append_token(head, new_token_str(&s[seg_start], *i - seg_start, 0));
			/* handle $ inside double quotes (expand allowed) */
			handle_dollar(s, i, head, 1);
			seg_start = *i;
			continue;
		}
		(*i)++;
	}
	if (seg_start < *i)
		append_token(head, new_token_str(&s[seg_start], *i - seg_start, 0));
	if (s[*i] == '"')
		(*i)++;
}

/* handle 'single quoted' section: produce one literal token (no expansion) */
static void	handle_single_quote(const char *s, int *i, t_token **head)
{
	int	start;

	/* skip opening ' */
	(*i)++;
	start = *i;
	while (s[*i] && s[*i] != '\'')
		(*i)++;
	/* add literal content even if it contains $ (not expandable) */
	if (start < *i)
		append_token(head, new_token_str(&s[start], *i - start, 0));
	if (s[*i] == '\'')
		(*i)++;
}

/* handle a normal unquoted word chunk until delimiter (space, op, quote, or $) */
static void	handle_unquoted_word(const char *s, int *i, t_token **head)
{
	int	start;

	start = *i;
	while (s[*i] && s[*i] != ' ' && !is_op_char(s[*i])
		&& s[*i] != '\'' && s[*i] != '"' && s[*i] != '$')
		(*i)++;
	if (start < *i)
		append_token(head, new_token_str(&s[start], *i - start, 0));
}

/* main tokenize */
t_token	*tokenize(const char *s)
{
	t_token	*head = NULL;
	int		i = 0;

	while (s[i])
	{
		/* spaces outside quotes are separate tokens */
		if (s[i] == ' ')
		{
			append_token(&head, new_token_str(" ", 1, 3));
			i++;
			continue;
		}
		/* operators outside quotes */
		if (is_op_char(s[i]))
		{
			if ((s[i] == '<' || s[i] == '>') && s[i + 1] == s[i])
			{
				append_token(&head, new_token_str(&s[i], 2, 1));
				i += 2;
			}
			else
			{
				append_token(&head, new_token_str(&s[i], 1, 1));
				i++;
			}
			continue;
		}
		/* quote handling */
		if (s[i] == '"')
		{
			handle_double_quote(s, &i, &head);
			continue;
		}
		if (s[i] == '\'')
		{
			handle_single_quote(s, &i, &head);
			continue;
		}
		/* dollar outside quotes */
		if (s[i] == '$')
		{
			/* outside single quotes here, so expand allowed (2) */
			handle_dollar(s, &i, &head, 1);
			continue;
		}
		/* unquoted word */
		handle_unquoted_word(s, &i, &head);
	}
	return (head);
}
