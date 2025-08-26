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
	expanded = expand_node((*cur)->token, data);
	if (!expanded)
		return (-1);
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
	int		ret;

	cur = *tokens;
	prev = NULL;
	while (cur)
	{
		ret = expand_and_maybe_remove(tokens, &cur, &prev, data);
		if (ret == -1)
		{
			free_token(*tokens);
			tokens = NULL;
			return ;
		}
		else if (ret)
			continue ;
		prev = cur;
		cur = cur->next;
	}
}
