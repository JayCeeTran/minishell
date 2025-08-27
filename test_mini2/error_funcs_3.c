/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_funcs_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:21:58 by jtran             #+#    #+#             */
/*   Updated: 2025/08/26 19:22:00 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_free_exit(char *msg, int excode, t_data *data, int parent)
{
	close_pipes_and_files(data, data->first);
	free_all_exit(msg, excode, data, parent);
}

void	malloc_fail(t_data *data, char **new_env, int parent)
{
	free_split(new_env);
	close_free_exit("Error: Malloc failed!\n", 1, data, parent);
}
