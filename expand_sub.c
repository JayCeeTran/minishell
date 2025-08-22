#include "minishell.h"

static void	expand_quotes(char c, int *in_single, int *in_double)
{
	if (c == '\'' && !*in_double)
		*in_single = !*in_single;
	else if (c == '"' && !*in_single)
		*in_double = !*in_double;
}

static void	expand_status_var(char **result, t_data *data, int *i)
{
	char	*val;

	val = ft_itoa(data->status);
	*result = ft_strjoin_free(*result, val);
	free(val);
	(*i)++;
}

static void	expand_env_var(char **result, char *input, t_data *data, int *i)
{
	int		start;
	char	*key;
	char	*val;

	start = ++(*i);
	while (input[*i] && is_valid_var_char(input[*i]))
		(*i)++;
	key = ft_substr(input, start, *i - start);
	val = get_env_value(key, data->env);
	*result = ft_strjoin_free(*result, val);
	free(key);
	(*i)--;
}

static void	expand_dollar(char **result, char *input, t_data *data,
		int *i)
{
	if (input[*i + 1] == '?')
		expand_status_var(result, data, i);
	else
		expand_env_var(result, input, data, i);
}

char	*expand_node(char *input, t_data *data)
{
	int		i;
	int		in_single;
	int		in_double;
	char	*result;

	i = 0;
	in_single = 0;
	in_double = 0;
	result = ft_strdup("");
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			expand_quotes(input[i], &in_single, &in_double);
		else if (input[i] == '$' && !in_single && input[i + 1])
			expand_dollar(&result, input, data, &i);
		else
			append_char(&result, input[i]);
		i++;
	}
	return (result);
}
