#include "minishell.h"

static int	is_redir_op(const char *s)
{
	if (!ft_strncmp(s, "<", 2) || !ft_strncmp(s, ">", 2)
		|| !ft_strncmp(s, "<<", 3) || !ft_strncmp(s, ">>", 3))
		return (1);
	return (0);
}

static void	add_redir(t_redir **head, char *redir, char *file)
{
	t_redir	*new;
	t_redir	*tmp;

	new = malloc(sizeof(t_redir));
	if (!new)
		return ;
	new->redir = ft_strdup(redir);
	new->file = ft_strdup(file);
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
}

static int	count_cmd_words(t_token *cur)
{
	int	count;

	count = 0;
	while (cur && (cur->is_operator != 1 || is_redir_op(cur->token)) 
		&& ft_strncmp(cur->token, "|", 2) != 0)
	{
		if (cur->is_operator != 1 || !is_redir_op(cur->token))
			count++;
		if (cur->is_operator == 1 && is_redir_op(cur->token))
			cur = cur->next;
		cur = cur->next;
	}
	return (count);
}

void	fill_redirections(t_cmd *cmd, t_token *start, t_token *end)
{
	t_token	*tmp;

	tmp = start;
	while (tmp && tmp != end)
	{
		if (tmp->is_operator == 1 && is_redir_op(tmp->token)
			&& tmp->next && tmp->next->is_operator != 1)
		{
			add_redir(&cmd->redirections, tmp->token, tmp->next->token);
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
}

char	**fill_cmd_array(t_token **cur)
{
	int		i;
	int		count;
	char	**cmd;

	count = count_cmd_words(*cur);
	cmd = ft_calloc(count + 1, sizeof(char *));
	if (!cmd)
		return (NULL);
	i = 0;
	while (*cur && !((*cur)->is_operator == 1 && !ft_strncmp((*cur)->token, "|", 2)))
	{
		if ((*cur)->is_operator == 1 && is_redir_op((*cur)->token))
		{
			if ((*cur)->next)
				*cur = (*cur)->next;
		}
		else
			cmd[i++] = ft_strdup((*cur)->token);
		*cur = (*cur)->next;
	}
	cmd[i] = NULL;
	return (cmd);
}
