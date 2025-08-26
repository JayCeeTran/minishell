#include "minishell.h"

/* handle "double quoted" section: produce token(s) for plain segments and $VAR inside */
static void	tokenize_double_quote(const char *s, int *i, t_token **head)
{
	int	seg_start;

	(*i)++;
	seg_start = *i;
	while (s[*i] && s[*i] != '"')
	{
		if (s[*i] == '$')
		{
			if (seg_start < *i)
				append_token(head, new_token_str(&s[seg_start], *i - seg_start, 0));
			tokenize_dollar(s, i, head, 1);
			seg_start = *i;
			continue;
		}
		(*i)++;
	}
	if (seg_start < *i)
		append_token(head, new_token_str(&s[seg_start], *i - seg_start, 0));
	else if (s[*i] == '"')
		append_token(head, new_token_str("", 0, 0));
	if (s[*i] == '"')
		(*i)++;
}

/* handle 'single quoted' section: produce one literal token (no expansion) */
static void	tokenize_single_quote(const char *s, int *i, t_token **head)
{
	int	start;

	(*i)++;
	start = *i;
	while (s[*i] && s[*i] != '\'')
		(*i)++;
	if (start < *i)
		append_token(head, new_token_str(&s[start], *i - start, 0));
	else if (s[*i] == '\'')
		append_token(head, new_token_str("", 0, 0));
	if (s[*i] == '\'')
		(*i)++;
}

int	tokenize_quotes_or_dollar(const char *s, int *i, t_token **head)
{
	if (s[*i] == '"')
	{
		tokenize_double_quote(s, i, head);
		return (1);
	}
	if (s[*i] == '\'')
	{
		tokenize_single_quote(s, i, head);
		return (1);
	}
	if (s[*i] == '$')
	{
		tokenize_dollar(s, i, head, 1);
		return (1);
	}
	return (0);
}
