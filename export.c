/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:33:43 by jtran             #+#    #+#             */
/*   Updated: 2025/08/26 18:03:58 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		add_env_var(t_data *data, char *s, int parent);
int		add_to_export_or_error(t_data *data, int compare, char *s, int parent);
void	swap_to_new_env(t_data *data, int i, char **new_env);

int	b_export(t_data *data, t_cmd *cmd, int parent)
{
	int	i;
	int	status_changed;

	status_changed = 0;
	i = 1;
	count_arguments_and_print_list(data, cmd, parent);
	while (cmd->cmd[i])
	{
		if (add_env_var(data, cmd->cmd[i], parent) == 0)
			status_changed = 1;
		i++;
	}
	if (status_changed)
		return (0);
	return (1);
}

int	add_env_var(t_data *data, char *s, int parent)
{
	int		compare;
	char	**new_env;
	int		i;
	int		exit;

	compare = env_strlen(s) + 1;
	exit = add_to_export_or_error(data, compare, s, parent);
	if (exit == 0)
		return (0);
	else if (exit == 1)
		return (1);
	remove_from_export_list(data, s, parent);
	new_env = NULL;
	i = add_env_helper(data, &new_env, s, parent);
	if (i >= 10000)
	{
		i -= 10000;
		new_env[i] = ft_strdup(s);
		if (!new_env[i++])
			malloc_fail(data, new_env, parent);
	}
	swap_to_new_env(data, i, new_env);
	return (1);
}

int	malloc_new_list(t_data *data, char ***new_env, int parent, char **list)
{
	int	e_size;

	e_size = envp_size(list);
	*new_env = malloc((e_size + 2) * sizeof(char *));
	if (!*new_env)
		close_free_exit("Error: Malloc failed!\n", 1, data, parent);
	(*new_env)[e_size + 1] = NULL;
	return (e_size);
}

int	add_to_export_or_error(t_data *data, int compare, char *s, int parent)
{
	if (compare == -1)
	{
		export_error(s);
		data->status = 1;
		return (0);
	}
	else if (compare == -2)
	{
		ft_putstr_fd("here\n", 2);
		add_to_export_list(data, s, parent);
		return (1);
	}
	return (2);
}

void	swap_to_new_env(t_data *data, int i, char **new_env)
{
	new_env[i] = NULL;
	free_split(data->my_env);
	data->my_env = new_env;
}
