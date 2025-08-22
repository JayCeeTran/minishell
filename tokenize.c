#include "minishell.h"

static int	tokenize_space(const char *s, int *i, t_token **head)
{
	if (s[*i] != ' ')
		return (0);
	append_token(head, new_token_str(" ", 1, 3));
	(*i)++;
	return (1);
}

static int	tokenize_operator(const char *s, int *i, t_token **head)
{
	if (!is_op_char(s[*i]))
		return (0);
	if ((s[*i] == '<' || s[*i] == '>') && s[*i + 1] == s[*i])
	{
		append_token(head, new_token_str(&s[*i], 2, 1));
		*i += 2;
	}
	else
	{
		append_token(head, new_token_str(&s[*i], 1, 1));
		(*i)++;
	}
	return (1);
}

/* handle a normal unquoted word chunk until delimiter (space, op, quote, or $) */
static void	tokenize_unquoted_word(const char *s, int *i, t_token **head)
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
	t_token	*head;
	int		i;

	head = NULL;
	i = 0;
	while (s[i])
	{
		if (tokenize_space(s, &i, &head))
			continue;
		if (tokenize_operator(s, &i, &head))
			continue;
		if (tokenize_quotes_or_dollar(s, &i, &head))
			continue;
		tokenize_unquoted_word(s, &i, &head);
	}
	return (head);
}
