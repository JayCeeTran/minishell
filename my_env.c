#include "minishell.h"

int	envp_size(char **env);

void my_envp(t_data *data)
{
	int env_size;
	char **my_env;
	int i;

	env_size = envp_size(data->env);
	my_env = malloc((env_size + 2) * sizeof(char *));
	i = 0;
	while(i < env_size)
	{
		my_env[i] = ft_strdup(data->env[i]);
		i++;
	}
	my_env[i] = NULL;
	data->my_env = my_env;
}

int	envp_size(char **env)
{
	int count;

	count = 0;
	while(env[count])
		count++;
	return(count);
}

int		env_strlen(char *s)
{
	int i = 0;
	while(s[i] && ((s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || s[i] == '_'))
		i++;
	if(s[i] == '=')
		return(i);
	return(-2);
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
			added = 1;
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

int		unset_strcmp(char *s1, char *s2)
{
	while(*s1 && *s2)
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

void	del_env_var(t_data *data, char *s)
{
	int e_size;
	char **new_env;
	int i;
	int j;

	i = 0;
	j = 0;
	e_size = envp_size(data->my_env);
	new_env = malloc((e_size + 1) * sizeof(char *));
	while(data->my_env[j])							
	{
		if(unset_strcmp(data->my_env[j], s) == 0)
			j++;
		if(data->my_env[j])
			new_env[i] = ft_strdup(data->my_env[j]);
		else if(!data->my_env[j])
			break;
		i++;
		j++;
	}
	new_env[i] = NULL;
	free_split(data->my_env);
	data->my_env = new_env;
}
