/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:34:23 by jtran             #+#    #+#             */
/*   Updated: 2025/08/26 16:08:32 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_split_index(char **split, int n)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (i < n)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_split_exit(char **cmd)
{
	free_split(cmd);
	err_msg_exit("Error\nReparsing failed\n", 1);
}

void	free_heredoc_paths(t_heredoc *heredoc)
{
	int	i;

	i = 0;
	while (i < heredoc->count)
	{
		free(heredoc->path[i]);
		i++;
	}
}

void	free_all_exit(char *s, int excode, t_data *data, int parent)
{
	free_split(data->path);
	free_split(data->my_env);
	free_split(data->export_list);
	if (data->list)
		free_cmd_list(data->list);
	if (parent)
		unlink("heredoc");
	if (excode == -1)
		exit(WEXITSTATUS(data->status));
	err_msg_exit(s, excode);
}
