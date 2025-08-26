/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_pwds_cd_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:25:17 by jtran             #+#    #+#             */
/*   Updated: 2025/08/26 19:25:19 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_pwd(t_data *data, int parent, char *opwd, int *i)
{
	if (ft_strncmp("PWD=", data->my_env[(*i)], 4) == 0)
	{
		free(data->my_env[(*i)]);
		data->my_env[(*i)] = new_pwd(data, parent, opwd, *i);
		return (1);
	}
	return (0);
}

int	find_oldpwd(t_data *data, int parent, char *opwd, int *i)
{
	int	env_size;
	int	check;

	check = 0;
	env_size = envp_size(data->my_env);
	if (ft_strncmp("OLDPWD=", data->my_env[(*i)], 7) == 0)
	{
		free(data->my_env[(*i)]);
		data->my_env[(*i)] = ft_strjoin("OLDPWD=", opwd);
		if (!data->my_env[(*i)])
		{
			make_my_env_freeable(data, opwd, *i, env_size);
			close_free_exit("Error: Malloc failed!\n", 1, data, parent);
		}
		check = 1;
	}
	return (check);
}
