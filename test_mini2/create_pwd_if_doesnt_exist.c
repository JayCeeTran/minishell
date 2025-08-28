#include "minishell.h"

int	find_pwds(t_data *data)
{
	int i;
	int check;

	i = 0;
	check = 0;
	while(data->my_env[i])
	{
		if(ft_strncmp("PWD=", data->my_env[i], 4) == 0)
			check++;
		if(ft_strncmp("OLDPWD=", data->my_env[i], 7) == 0)
			check++;
		i++;
	}
	if(check != 2)
		return(0);
	return(1);
}

void	add_pwd(t_data *data, int parent, int *i, char **newlist)
{
	newlist[(*i)] = ft_strdup("PWD=");
	if(!newlist[(*i)])
		malloc_fail(data, newlist, parent);
	(*i)++;
}

void	add_opwd(t_data *data, int parent, int *i, char **newlist)
{
	newlist[(*i)] = ft_strdup("OLDPWD=");
	if(!newlist[(*i)])
		malloc_fail(data, newlist, parent);
	(*i)++;
}

int	initialize(char ***newlist, int *l_size, t_data *data, int parent)
{
	*l_size = envp_size(data->my_env);
	*newlist = malloc((*l_size + 5) * sizeof(char *));
	if(!*newlist)
		close_free_exit("Error: Malloc Failed!\n", 1, data, parent);
	return(0);
}

int	dup_pwd(t_data *data, char **newlist, int i)
{
	newlist[i] = ft_strdup(data->my_env[i]);
	return(1);
}

void	create_newlist_add_both(t_data *data, int parent, int opwd, int pwd)
{
	char **newlist;
	int l_size;
	int i;

	i = initialize(&newlist, &l_size, data, parent);
	while(data->my_env[i])
	{
		if(!pwd && ft_strncmp("PWD=", data->my_env[i], 4) == 0)
			pwd = dup_pwd(data, newlist, i);
		else if(!opwd && ft_strncmp("OLDPWD=", data->my_env[i], 7) == 0)
			opwd = dup_pwd(data, newlist, i);
		else
			newlist[i] = ft_strdup(data->my_env[i]);
		if(!newlist[i])
			malloc_fail(data, newlist, parent);
		i++;
	}
	if(!pwd)
		add_pwd(data, parent, &i, newlist);
	if(!opwd)
		add_opwd(data, parent, &i, newlist);
	swap_to_new_env(data, i, newlist);
}

void	create_pwd_if_doesnt_exist(t_data *data, int parent)
{
	if(!find_pwds(data))
		create_newlist_add_both(data, parent, 0, 0);
	return;
}
