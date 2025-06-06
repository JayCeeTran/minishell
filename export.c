#include "minishell.h"

int	env_strlen(char *s);
void	add_env_var(t_data *data, char *s);

int		b_export(t_data *data, t_cmd *cmd)
{
	int i;

	i = 1;
	while(cmd->cmd[i])
	{
		add_env_var(data, cmd->cmd[i]);
		i++;
	}
	return(1);
}

void	add_env_var(t_data *data, char *s)
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
	while(i < e_size)
	{
		if(ft_strncmp(s, data->my_env[i], compare) == 0)
		{
			new_env[i] = ft_strdup(s);
			added = 1; //to prevent duplicates
		}
		else
			new_env[i] = ft_strdup(data->my_env[i]);
		i++;
	}
	if(!added)
		new_env[i++] = ft_strdup(s);
	new_env[i] = NULL;
	free_split(data->my_env);
	data->my_env = new_env;
}

int	env_strlen(char *s)
{
	int i;

	i = 0;
	while(s[i] && ((s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || s[i] == '_'))
		i++;
	if(s[i] == '=')
		return(i);
	return(-2);
}
