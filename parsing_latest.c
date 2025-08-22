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
static char	**fill_cmd_array(t_token **cur)
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
t_cmd	*parse_cmd_list(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*cur_cmd;
	t_cmd	*last;
	t_token	*cur;
	t_token	*cur_save;

	head = NULL;
	cur = tokens;
	while (cur)
	{
		cur_cmd = malloc(sizeof(t_cmd));
		if (!cur_cmd)
			return (NULL);
		cur_cmd->redirections = NULL;
		cur_cmd->pipe = 0;
		cur_cmd->next = NULL;
		cur_save = cur;
		cur_cmd->cmd = fill_cmd_array(&cur);

		t_token *tmp = cur_save;
		while (tmp && tmp != cur)
		{
			if (tmp->is_operator == 1 && is_redir_op(tmp->token)
				&& tmp->next && tmp->next->is_operator != 1)
			{
				add_redir(&cur_cmd->redirections, tmp->token, tmp->next->token);
				tmp = tmp->next;
			}
			tmp = tmp->next;
		}

		if (cur && cur->is_operator == 1 && !ft_strncmp(cur->token, "|", 2))
		{
			cur_cmd->pipe = 1;
			cur = cur->next;
		}
		if (!head)
			head = cur_cmd;
		else
			last->next = cur_cmd;
		last = cur_cmd;
	}
	return (head);
}
