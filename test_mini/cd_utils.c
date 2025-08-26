/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:15:47 by jtran             #+#    #+#             */
/*   Updated: 2025/08/26 19:15:52 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_home_from_my_env(t_data *data, char **home)
{
	int	i;

	i = 0;
	while (data->my_env[i])
	{
		if (ft_strncmp(data->my_env[i], "HOME=", 5) == 0)
			*home = ft_substr(data->my_env[i], 5, 200);
		i++;
	}
}

void	make_my_env_freeable(t_data *data, char *opwd, int index, int env_size)
{
	free(opwd);
	data->my_env[index] = NULL;
	free_split_index(data->my_env, env_size);
	data->my_env = NULL;
}

void	cd_error_msg(t_data *data, t_cmd *cmd, int error, int *status_changed)
{
	if (error)
	{
		write_bash();
		write(2, "cd: ", 4);
		if (cmd->cmd[1])
			ft_putstr_fd(cmd->cmd[1], 2);
		write(2, ": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 1);
		data->status = 1;
		*status_changed = 1;
	}
}

int	cd_home(t_data *data, t_cmd *cmd, char *opwd, int parent)
{
	char	*home;
	int		error;

	error = 0;
	home = NULL;
	if (!cmd->cmd[1])
	{
		find_home_from_my_env(data, &home);
		if (chdir(home) == 0)
			change_dir_helper(data, opwd, parent);
		else
			error = 1;
	}
	else if (cmd->cmd[1] && chdir(cmd->cmd[1]) == 0)
		change_dir_helper(data, opwd, parent);
	else
		error = 1;
	if (home)
		free(home);
	return (error);
}
