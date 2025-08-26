/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:33:38 by jtran             #+#    #+#             */
/*   Updated: 2025/08/26 17:59:09 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	newlist_to_data(t_data *data, char **new_list, int i);

int	check_my_env_for_duplicate(char *s, t_data *data)
{
	int	i;

	i = 0;
	while (data->my_env[i])
	{
		if (unset_strcmp(data->my_env[i], s) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	add_to_export_list(t_data *data, char *s, int parent)
{
	int		i;
	char	**new_list;

	new_list = NULL;
	if (check_my_env_for_duplicate(s, data))
		return ;
	i = add_export_helper(data, &new_list, s, parent);
	if (i >= 10000)
	{
		i -= 10000;
		new_list[i] = ft_strdup(s);
		if (!new_list[i++])
			malloc_fail(data, new_list, parent);
	}
	ft_putstr_fd("hereeeeee2\n", 2);
	newlist_to_data(data, new_list, i);
}

void	remove_from_export_list(t_data *data, char *s, int parent)
{
	int		l_size;
	char	**new_list;
	int		i;
	int		j;

	i = 0;
	j = 0;
	l_size = envp_size(data->export_list);
	new_list = malloc((l_size + 1) * sizeof(char *));
	if (!new_list)
		close_free_exit("Error: Malloc failed!\n", 1, data, parent);
	while (data->export_list[j])
	{
		if (unset_strcmp(s, data->export_list[j]) == 0)
		{
			j++;
			continue ;
		}
		new_list[i] = ft_strdup(data->export_list[j]);
		if (!new_list[i])
			malloc_fail(data, new_list, parent);
		i++;
		j++;
	}
	newlist_to_data(data, new_list, i);
}

static void	newlist_to_data(t_data *data, char **new_list, int i)
{
	new_list[i] = NULL;
	free_split(data->export_list);
	data->export_list = new_list;
}
