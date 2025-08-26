/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env_var_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:30:30 by jtran             #+#    #+#             */
/*   Updated: 2025/08/26 18:28:23 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_env_helper(t_data *data, char ***new_env, char *s, int parent)
{
	int	e_size;
	int	i;
	int	compare;
	int	added;

	i = 0;
	added = 0;
	compare = env_strlen(s) + 1;
	e_size = malloc_new_list(data, new_env, parent, data->my_env);
	while (i < e_size)
	{
		if (!added && ft_strncmp(s, data->my_env[i], compare) == 0)
		{
			(*new_env)[i] = ft_strdup(s);
			added = 1;
		}
		else
			(*new_env)[i] = ft_strdup(data->my_env[i]);
		if (!(*new_env)[i])
			malloc_fail(data, *new_env, parent);
		i++;
	}
	if (!added)
		i += 10000;
	return (i);
}

int	add_export_helper(t_data *data, char ***new_env, char *s, int parent)
{
	int	e_size;
	int	i;
	int	added;

	i = 0;
	added = 0;
	ft_putstr_fd("heel\n", 2);
	e_size = malloc_new_list(data, new_env, parent, data->export_list);
	while (i < e_size)
	{
		ft_putstr_fd("i2\n", 2);
		printf("%s %d\n", s, i);
		if (!added && ft_strcmp(s, data->export_list[i]) == 0)
		{
			(*new_env)[i] = ft_strdup(s);
			added = 1;
		}
		else
			(*new_env)[i] = ft_strdup(data->export_list[i]);
		if (!(*new_env)[i])
			malloc_fail(data, *new_env, parent);
		i++;
	}
	ft_putstr_fd("heellooo\n", 2);
	if (!added)
		i += 10000;
	return (i);
}
