/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_my_env_to_print.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:36:40 by jtran             #+#    #+#             */
/*   Updated: 2025/08/26 15:36:42 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		strcmp_my_env(char *s1, char *s2);
void	sort_list(char **list);
void	swap_pointers(char **s1, char **s2);
void	free_list_exit(t_data *data, char **temp, int parent);

void	sort_my_env(t_data *data, int parent, int i, int j)
{
	char	*list[100];

	while (data->my_env[i])
	{
		list[i] = ft_strdup(data->my_env[i]);
		if (!list[i])
			free_list_exit(data, list, parent);
		i++;
	}
	while (data->export_list[j])
	{
		list[i] = ft_strdup(data->export_list[j]);
		if (!list[i])
			free_list_exit(data, list, parent);
		i++;
		j++;
	}
	list[i] = NULL;
	sort_list(list);
	print_export_list(list);
	j = 0;
	while (j < i)
		free(list[j++]);
}

void	sort_list(char **list)
{
	int	i;
	int	j;

	i = 0;
	while (list[i])
	{
		j = i + 1;
		while (list[j])
		{
			if (strcmp_my_env(list[i], list[j]) > 0)
			{
				swap_pointers(&list[i], &list[j]);
				j = i;
			}
			j++;
		}
		i++;
	}
}

int	strcmp_my_env(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] == '=')
			return (-1);
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	swap_pointers(char **s1, char **s2)
{
	char	*temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

void	free_list_exit(t_data *data, char **temp, int parent)
{
	int	i;

	i = 0;
	while (temp[i])
		free(temp[i++]);
	close_free_exit("Error: Malloc failed!\n", 1, data, parent);
}
