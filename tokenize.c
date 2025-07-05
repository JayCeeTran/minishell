#include "minishell.h"

#include "minishell.h"

static int	is_operator_char(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

static int	word_has_dollar(const char *s, int i)
{
	while (s[i] && s[i] != ' ')
	{
		if (s[i] == '$')
			return (1);
		if ((s[i] == '\'' || s[i] == '\"'))
		{
			char quote = s[i++];
			while (s[i] && s[i] != quote)
				i++;
		}
		i++;
	}
	return (0);
}

static int	add_token(t_token **head, const char *start, int len, int is_op)
{
	t_token	*new;
	t_token	*tmp;

	if (len == 0)
		return (0);
	new = malloc(sizeof(t_token));
	if (!new)
		return (0);
	new->token = ft_substr(start, 0, len);
	new->is_operator = is_op;
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

static int	skip_quotes(const char *s, int *i, char *buf, int *j)
{
	char	quote;

	quote = s[*i];
	(*i)++;
	while (s[*i] && s[*i] != quote)
		buf[(*j)++] = s[(*i)++];
	if (s[*i] == quote)
		(*i)++;
	return (0);
}

static void	process_word(const char *s, int *i, t_token **head)
{
	char	buf[1024];
	int		j;

	j = 0;
	if (word_has_dollar(s, *i))
	{
		// Copy everything until next space into buf
		while (s[*i] && s[*i] != ' ')
			buf[j++] = s[(*i)++];
		add_token(head, buf, j, 0);
		return ;
	}
	while (s[*i] && s[*i] != ' ')
	{
		if (s[*i] == '\'' || s[*i] == '\"')
			skip_quotes(s, i, buf, &j);
		else if (is_operator_char(s[*i]))
		{
			if (j > 0)
				add_token(head, buf, j, 0);
			j = 0;
			if ((s[*i] == '<' || s[*i] == '>') && s[*i + 1] == s[*i])
				add_token(head, &s[*i], 2, 1), (*i) += 2;
			else
				add_token(head, &s[*i], 1, 1), (*i)++;
		}
		else
			buf[j++] = s[(*i)++];
	}
	if (j > 0)
		add_token(head, buf, j, 0);
}

t_token	*tokenize(const char *s)
{
	t_token	*head;
	int		i;

	i = 0;
	head = NULL;
	while (s[i])
	{
		if (s[i] == ' ')
			i++;
		else
			process_word(s, &i, &head);
	}
	return (head);
}
