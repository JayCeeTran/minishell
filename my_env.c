#include "minishell.h"

char **create_export_list(void);

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
		if(!my_env[i])
		{
			free_split(my_env);
			err_msg_exit("Error: Malloc failed!\n", 1);
		}
		i++;// check again. This happens before read_list. do we need to free all?
	}
	my_env[i] = NULL;
	data->my_env = my_env;
	data->export_list = create_export_list();
}

char **create_export_list(void)
{
	char **temp;

	temp = malloc(sizeof(char *));
	temp[0] = NULL;
	return(temp);
}

int	envp_size(char **env)
{
	int count;

	count = 0;
	while(env[count])
		count++;
	return(count);
}
