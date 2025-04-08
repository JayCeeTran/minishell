#include "minishell.h"

int main(int ac, char **av, char **env)
{
	av++;
	ac++;
	char **dest = malloc(3 * sizeof(char *));

	dest[0] = ft_strdup("cat");
	dest[1] = ft_strdup("\\a");
	dest[2] = NULL;
	pid_t pid;
	
	pid = fork();
	if(pid == 0)
		execve("/usr/bin/cat", dest, env);
	printf("fails\n");
	return(0);
}
