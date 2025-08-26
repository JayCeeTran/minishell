#include "minishell.h"

int	is_op_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

t_token	*new_token_str(const char *s, size_t len, int is_op)
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

void	append_token(t_token **head, t_token *node)
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
