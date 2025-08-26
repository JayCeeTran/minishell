/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_e_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:34:04 by jtran             #+#    #+#             */
/*   Updated: 2025/08/26 15:34:09 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_e_variable(char *var, t_data *data, int len)
{
	int		i;
	char	*temp;

	i = 0;
	while (data->my_env[i])
	{
		if (ft_strncmp(var, data->my_env[i], len) == 0)
			temp = ft_strdup(&data->my_env[i][len]);
	}
	return (temp);
}
