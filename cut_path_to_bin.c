#include "minishell.h"

void	find_path(t_data *data, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			data->path = ft_split(env[i] + 5, ':');
			if (!data->path)
				err_msg_exit("Error: Failed to malloc envp\n", 1);
			break ;
		}
		i++;
	}
	if (!env[i])
		err_msg_exit("Error: No PATH= found\n", 1);
}
