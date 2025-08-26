/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:34:32 by jtran             #+#    #+#             */
/*   Updated: 2025/08/26 15:34:33 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_cmd(t_cmd *cmd)
{
	int		i;
	t_redir	*tmp;

	if (!cmd)
		return ;
	if (cmd->cmd)
	{
		i = 0;
		while (cmd->cmd[i])
			free(cmd->cmd[i++]);
		free(cmd->cmd);
	}
	while (cmd->redirs)
	{
		tmp = cmd->redirs;
		cmd->redirs = cmd->redirs->next;
		free(tmp->redir);
		free(tmp->file);
		free(tmp);
	}
	free(cmd);
}

void	free_cmd_list(t_cmd *head)
{
	t_cmd	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free_cmd(tmp);
	}
}

void	free_token(t_token *head)
{
	t_token	*tmp;

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
