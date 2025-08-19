#include "minishell.h"

int	env_strlen(char *s);
int	add_env_var(t_data *data, char *s, int parent);
void	count_arguments_and_print_list(t_data *data, t_cmd *cmd, int parent);
void	print_export_list(char **list);
void	print_my_env_with_quotes(char *s);

int	b_export(t_data *data, t_cmd *cmd, int parent)
{
	int i;
	int status_changed;

	status_changed = 0;
	i = 1;
	count_arguments_and_print_list(data, cmd, parent);
	while(cmd->cmd[i])
	{
		if(add_env_var(data, cmd->cmd[i], parent) == 0)
			status_changed = 1;
		i++;
	}
	if(status_changed)
		return(0);
	return(1);
}

void	count_arguments_and_print_list(t_data *data, t_cmd *cmd, int parent)
{
	int i;

	i = 1;
	while(cmd->cmd[i])
		i++;
	if(i == 1)
		sort_my_env(data, parent);
}

void	print_export_list(char **list)
{
	int i;

	i = 0;
	while(list[i])
	{
		ft_putstr_fd("declare -x ", 1);
		print_my_env_with_quotes(list[i]);
		i++;
	}
}

void	print_my_env_with_quotes(char *s)
{
	int i;
	int quote;

	quote = 0;
	i = 0;
	while(s[i])
	{
		write(1, &s[i], 1);
		if(s[i] == '=')
		{	
			write(1, "\"", 1);
			quote = 1;
		}
		i++;
	}
	if(quote)
		write(1, "\"", 1);
	write(1, "\n", 1);
}

int	add_env_var(t_data *data, char *s, int parent)
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
		data->status = 1;
		return(0);
	}
	else if(compare == -2)
	{
		add_to_export_list(data, s, parent);
		return(1);
	}
	remove_from_export_list(data, s, parent);
	i = 0;
	e_size = envp_size(data->my_env);
	new_env = malloc((e_size + 2) * sizeof(char *));
	if(!new_env)
		close_free_exit("Error: Malloc failed!\n", 1, data, parent);
	while(i < e_size)
	{
		if(!added && ft_strncmp(s, data->my_env[i], compare) == 0)
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
	{
		new_env[i] = ft_strdup(s);
		if(!new_env[i++])
			malloc_fail(data, new_env, parent);
	}
	new_env[i] = NULL;
	free_split(data->my_env);
	data->my_env = new_env;
	return(1);
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
	while(s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	if(s[i] == '=')
		return(i);
	if(s[i] == '\0')
		return(-3);
	return(-2);
}
			// unset from both list

