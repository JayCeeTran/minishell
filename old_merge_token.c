#include "minishell.h"


static void merge_tokens(t_token *head)
{
	t_token *cur = head;

	while (cur && cur->next)
	{
		if ((cur->is_operator != 1 && cur->is_operator != 3) 
			&& (cur->next->is_operator != 1 && cur->next->is_operator != 3))
		{
			cur->token = ft_strjoin_free(cur->token, cur->next->token);
			t_token *tmp = cur->next;
			cur->next = tmp->next;
			free(tmp->token);
			free(tmp);
			continue;
		}
		cur = cur->next;
	}
}

static void remove_space(t_token **head)
{
	t_token *cur = *head;
	t_token *prev = NULL;

	while (cur)
	{
		if (cur->is_operator == 3 && ft_strncmp(cur->token, " ", 2) == 0)
		{
			t_token *tmp = cur;
			if (prev)
				prev->next = cur->next;
			else
				*head = cur->next;
			cur = cur->next;
			free(tmp->token);
			free(tmp);
			continue;
		}
		prev = cur;
		cur = cur->next;
	}
}

void simplify_tokens(t_token **head)
{
	merge_tokens(*head);
	remove_space(head);
}
