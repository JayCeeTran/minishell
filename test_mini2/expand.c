/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:23:06 by jtran             #+#    #+#             */
/*   Updated: 2025/08/27 17:50:20 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append_char(char **dst, char c)
{
	char	buf[2];

	buf[0] = c;
	buf[1] = '\0';
	*dst = ft_strjoin_free(*dst, buf);
	if (!(*dst))
		return (-1);
	return (1);
}

char	*get_env_value(char *key, char **envp)
{
	int	i;
	int	len;

	len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], key, len) && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return ("");
}

int	has_dollar(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

static int	expand_and_maybe_remove(t_token **tokens, t_token **cur,
		t_token **prev, t_data *data)
{
	char	*expanded;
	t_token	*to_delete;

	if (!has_dollar((*cur)->token) || (*cur)->is_op != 2)
		return (0);
	expanded = expand_node((*cur)->token, data, *tokens);
	free((*cur)->token);
	(*cur)->token = expanded;
	if ((*cur)->token[0] != '\0')
		return (0);
	to_delete = *cur;
	if (*prev)
		(*prev)->next = (*cur)->next;
	else
		*tokens = (*cur)->next;
	*cur = (*cur)->next;
	free(to_delete->token);
	free(to_delete);
	return (1);
}

void	expand_token(t_token **tokens, t_data *data)
{
	t_token	*cur;
	t_token	*prev;

	cur = *tokens;
	if (!cur)
		return;
	prev = NULL;
	while (cur)
	{
		if (expand_and_maybe_remove(tokens, &cur, &prev, data))
			continue ;
		prev = cur;
		cur = cur->next;
	}
}
