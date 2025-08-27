#include "minishell.h"

char *find_pwd_from_env(t_data *data, int parent)
{
	int i;
	char *temp;

	i = 0;
	temp = NULL;
	while(data->my_env[i])
	{
		if(ft_strncmp("PWD=", data->my_env[i], 4) == 0)
		{
			temp = ft_strdup(data->my_env[i]);
			if(!temp)
				free_all_exit("Error: Malloc Failed!\n", 1, data, parent);
		}
		i++;	
	}
	return(temp);
}
