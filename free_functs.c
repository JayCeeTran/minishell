#include "minishell.h"

void	free_split(char **split)
{
	int i;

	i = 0;
	while(split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_split_exit(char **cmd)
{
	free_split(cmd);
	err_msg_exit("Error\nReparsing failed\n");
}
