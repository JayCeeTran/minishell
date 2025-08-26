/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_bin_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:33:49 by jtran             #+#    #+#             */
/*   Updated: 2025/08/26 15:33:52 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_to_path(t_cmd *cmd, t_data *data)
{
	int		i;
	char	*path;
	char	*slash;

	i = 0;
	while (data->path[i])
	{
		slash = ft_strjoin(data->path[i], "/");
		if (!slash)
			close_free_exit("Error: Malloc Failed!\n", 1, data, 0);
		path = ft_strjoin(slash, cmd->cmd[0]);
		if (!path)
		{
			free(slash);
			close_free_exit("Error: Malloc Failed!\n", 1, data, 0);
		}
		free(slash);
		if (check_existence_permission(path, data, cmd))
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

int	is_there_slash(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	check_existence_permission(char *s, t_data *data, t_cmd *cmd)
{
	int	fd;

	if (access(s, F_OK) == 0)
	{
		fd = open(s, O_WRONLY);
		if (fd > 1)
			close(fd);
		else if (fd == -1 && errno == EISDIR)
		{
			is_dir_error(s);
			close_free_exit(NULL, 1, data, 0);
		}
		if (access(s, X_OK) == 0)
			return (1);
		else
		{
			no_permission(cmd->cmd[0]);
			close_free_exit(NULL, 126, data, 0);
		}
	}
	return (0);
}
