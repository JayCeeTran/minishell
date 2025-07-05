#include "minishell.h"

int	env_strlen(char *s);
void	add_env_var(t_data *data, char *s, int parent);

int	b_export(t_data *data, t_cmd *cmd, int parent)
{
	int i;

	i = 1;
	while(cmd->cmd[i])
	{
		add_env_var(data, cmd->cmd[i], parent);
		i++;
	}
	return(1);
}

void	add_env_var(t_data *data, char *s, int parent)
{
	int e_size;
	char **new_env;
	int i;
	int compare;
	int added;
	
	added = 0;
	compare = env_strlen(s) + 1; //Maybe hide envs with no '='
	if(compare == -1)
	{
		export_error(s);
		return;
	}
	i = 0;
	e_size = envp_size(data->my_env);
	new_env = malloc((e_size + 2) * sizeof(char *));
	if(!new_env)
		close_free_exit("Error: Malloc failed!\n", 1, data, parent);
	while(i < e_size)
	{
		if(ft_strncmp(s, data->my_env[i], compare) == 0) //recheck if strlen returns -2, what if its only export myvar "this is where it returns -2"
		{
			new_env[i] = ft_strdup(s);
			added = 1; //to prevent duplicates
		}
		else
			new_env[i] = ft_strdup(data->my_env[i]);
		if(!new_env[i])
			malloc_fail(data, new_env, parent);
		i++;
	}
	if(!added)
		new_env[i] = ft_strdup(s);
	if(!new_env[i++])
		malloc_fail(data, new_env, parent);
	new_env[i] = NULL;
	free_split(data->my_env);
	data->my_env = new_env;
}

void	malloc_fail(t_data *data, char **new_env, int parent)
{
	free_split(new_env);
	close_free_exit("Error: Malloc failed!\n", 1, data, parent);
}

int	env_strlen(char *s)
{
	int i;

	i = 0;
	while(s[i] && s[i] != '=' && ((s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || s[i] == '_'))
		i++;
	if(s[i] == '=')
		return(i);
	return(-2);
}
