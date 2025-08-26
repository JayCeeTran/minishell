/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:33:24 by jtran             #+#    #+#             */
/*   Updated: 2025/08/26 15:33:26 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_quotes(char c, int *in_single, int *in_double)
{
	if (c == '\'' && !*in_double)
		*in_single = !*in_single;
	else if (c == '"' && !*in_single)
		*in_double = !*in_double;
}

static int	expand_status_var(char **result, t_data *data, int *i)
{
	char	*val;

	val = ft_itoa(data->status);
	if (!val)
		return (-1);
	*result = ft_strjoin_free(*result, val);
	if (!(*result))
		return (-1);
	free(val);
	(*i)++;
	return (1);
}

static int	expand_env_var(char **result, char *input, t_data *data, int *i)
{
	int		start;
	char	*key;
	char	*val;

	start = ++(*i);
	while (input[*i] && is_valid_var_char(input[*i]))
		(*i)++;
	key = ft_substr(input, start, *i - start);
	if (!key)
		return (-1);
	val = get_env_value(key, data->my_env);
	*result = ft_strjoin_free(*result, val);
	if (!(*result))
	{
		free(key);
		return (-1);
	}
	free(key);
	(*i)--;
	return (1);
}

static int	expand_dollar(char **result, char *input, t_data *data, int *i)
{
	if (input[*i + 1] == '?')
		return (expand_status_var(result, data, i));
	else
		return (expand_env_var(result, input, data, i));
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
		{
			if (expand_dollar(&result, input, data, &i) == -1)
				return (NULL);
		}
		else if (append_char(&result, input[i]) == -1)
			return (NULL);
		i++;
	}
	return (result);
}
