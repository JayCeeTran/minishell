#include "minishell.h"

static void	free_cmd(t_cmd *cmd)
{
	int i;

	if (!cmd)
		return ;
	if (cmd->cmd)
	{
		i = 0;
		while (cmd->cmd[i])
			free(cmd->cmd[i++]);
		free(cmd->cmd);
	}
	while (cmd->redirections)
	{
		t_redir *tmp = cmd->redirections;
		cmd->redirections = cmd->redirections->next;
		free(tmp->redir);
		free(tmp->file);
		free(tmp);
	}
	free(cmd);
}

void	free_cmd_list(t_cmd *head)
{
	t_cmd *tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free_cmd(tmp);
	}
}

void free_token(t_token *head)
{
	t_token *tmp;

	while (head != NULL)
	{
		tmp = head->next;
		free(head->token);
		free(head);
		head = tmp;
	}
}

int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*res;
	
	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}
