#include "minishell.h"

int		unset_strcmp(char *s1, char *s2);
void	del_env_var(t_data *data, char *s, int parent);

int b_unset(t_data *data, t_cmd *cmd, int parent)
{
	int i;

	i = 1;
	while(cmd->cmd[i])
	{
		del_env_var(data, cmd->cmd[i], parent);
		i++;
	}
	return(1);
}

void	del_env_var(t_data *data, char *s, int parent)
{
	int e_size;
	char **new_env;
	int i;
	int j;

	i = 0;
	j = 0;
	e_size = envp_size(data->my_env); //what if s is NULL
	new_env = malloc((e_size + 1) * sizeof(char *));
	if(!new_env)
		close_free_exit("Error: Malloc failed!\n", 1, data, parent);
	while(data->my_env[j])							
	{
		if(unset_strcmp(data->my_env[j], s) == 0)
		{
			j++;
			continue; //skip the string to unset, copy rest
		}
	//	if(data->my_env[j])
		new_env[i] = ft_strdup(data->my_env[j]);
		if(!new_env[i])
			malloc_fail(data, new_env, parent);
		i++;
		j++;
	}
	new_env[i] = NULL;
	free_split(data->my_env);
	data->my_env = new_env;
}

int		unset_strcmp(char *s1, char *s2)
{
	while(*s1 && *s2) 	//recheck the logic
	{
		if(*s1 != *s2)
			return(*s1 - *s2);
		if(*s1 == '=')
			return(-1);
		s1++;
		s2++;
	}
	if(*s2 == '\0' && *s1 == '=')
		return(0);
	return(*s1 - *s2);
}
