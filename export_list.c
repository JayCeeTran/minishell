#include "minishell.h"

static void	newlist_to_data(t_data *data, char **new_list, int i);

int	check_my_env_for_duplicate(char *s, t_data *data)
{
	int i;

	i = 0;
	while(data->my_env[i])
	{
		if(unset_strcmp(data->my_env[i], s) == 0)
			return(1);
		i++;
	}
	return(0);
}

void add_to_export_list(t_data *data, char *s, int parent)
{
	char **new_list;
	int l_size;
	int i;
	int added;

	if(check_my_env_for_duplicate(s, data))
		return;
	added = 0;
	i = 0;
	l_size = envp_size(data->export_list);
	new_list = malloc((l_size + 2) * sizeof(char *));
	if(!new_list)
		close_free_exit("Error: Malloc failed!\n", 1, data, parent);
	while(i < l_size)
	{
		if(!added && ft_strcmp(s, data->export_list[i]) == 0)
		{
			new_list[i] = ft_strdup(s);
			added = 1;
		}
		else
			new_list[i] = ft_strdup(data->export_list[i]);
		if(!new_list[i])
			malloc_fail(data, new_list, parent);
		i++;
	}
	if(!added)
	{
		new_list[i] = ft_strdup(s);
		if(!new_list[i++])
			malloc_fail(data, new_list, parent);
	}
	newlist_to_data(data, new_list, i);
}

void	remove_from_export_list(t_data *data, char *s, int parent)
{
	int l_size;
	char **new_list;
	int i;
	int j;

	i = 0;
	j = 0;
	l_size = envp_size(data->export_list);
	new_list = malloc((l_size + 1) * sizeof(char *));
	if(!new_list)
		close_free_exit("Error: Malloc failed!\n", 1, data, parent);
	while(data->export_list[j])
	{
		if(unset_strcmp(s, data->export_list[j]) == 0)
		{
			j++;
			continue;
		}
		new_list[i] = ft_strdup(data->export_list[j]);
		if(!new_list[i])
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
