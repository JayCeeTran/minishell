#include "minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*res;
	
	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*get_env_value(char *key, char **envp)
{
	int		i;
	int		len;

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

void	append_char(char **dst, char c)
{
	char	buf[2];

	buf[0] = c;
	buf[1] = '\0';
	*dst = ft_strjoin_free(*dst, buf);
}

static char	*expand_node(char *input, char **envp)
{
	int		i = 0;
	int		in_single = 0;
	int		in_double = 0;
	char	*result = ft_strdup("");

	while (input[i])
	{
		if (input[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (input[i] == '"' && !in_single)
			in_double = !in_double;
		else if (input[i] == '$' && !in_single && input[i + 1])
		{
			int		start = ++i;
			while (input[i] && is_valid_var_char(input[i]))
				i++;
			char	*key = ft_substr(input, start, i - start);
			char	*val = get_env_value(key, envp);
			result = ft_strjoin_free(result, val);
			free(key);
			i--;
		}
		else
			append_char(&result, input[i]);
		i++;
	}
	return (result);
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

void	expand_token(t_token *token, char **envp)
{
	t_token	*cur;
	char	*expanded;

	cur = token;
	while (cur)
	{
		if (has_dollar(cur->token) && cur->is_operator == 2)
		{
			expanded = expand_node(cur->token, envp);
			free(cur->token);
			cur->token = expanded;
		}
		cur = cur->next;
	}
}
