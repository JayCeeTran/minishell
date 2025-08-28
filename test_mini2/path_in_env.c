#include "minishell.h"

int path_in_env(t_data *data)
{
	int i;
	
	i = 0;
	while(data->my_env[i])
	{
		if(ft_strncmp("PATH=", data->my_env[i], 5) == 0)
			return(1);
		i++;
	}
	return(0);
}
