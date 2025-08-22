#include "minishell.h"

static void	tokenize_dollar_status(const char *s, int *i,
				t_token **head, int expand, int start)
{
	(*i)++;
	append_token(head, new_token_str(&s[start], *i - start, expand));
}

static void	tokenize_dollar_quoted(const char *s, int *i,
				t_token **head, int expand, int start)
{
	char	q;

	q = s[(*i)++];
	while (s[*i] && s[*i] != q)
		(*i)++;
	if (s[*i] == q)
		(*i)++;
	append_token(head, new_token_str(&s[start], *i - start, expand));
}

static void	tokenize_dollar_invalid(const char *s, t_token **head, int start)
{
	append_token(head, new_token_str(&s[start], 1, 0));
}

static void	tokenize_dollar_var(const char *s, int *i,
				t_token **head, int expand, int start)
{
	while (s[*i] && is_valid_var_char(s[*i]))
		(*i)++;
	append_token(head, new_token_str(&s[start], *i - start, expand));
}

void	tokenize_dollar(const char *s, int *i, t_token **head, int outside_single)
{
	int	start;
	int	expand;

	start = *i;
	(*i)++;
	expand = outside_single ? 2 : 0;
	if (s[*i] == '?')
		tokenize_dollar_status(s, i, head, expand, start);
	else if (s[*i] == '\'' || s[*i] == '"')
		tokenize_dollar_quoted(s, i, head, expand, start);
	else if (!is_valid_var_char(s[*i]))
		tokenize_dollar_invalid(s, head, start);
	else
		tokenize_dollar_var(s, i, head, expand, start);
}
