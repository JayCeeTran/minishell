#include "minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\nminishell> ", 12);
}

int	main(int ac, char **argv, char **env)
{
//	char *input = NULL;
	(void)ac;
	(void)argv;
//	env++;
//	t_data data;
//	data.env = env;

	testing(env);	//	signal(SIGINT, sigint_handler);
/*	while(1)
	{
		char *input = readline("minishell$ ");
		if(!input)
		{
			printf("control d\n");
			break;
		}
		if(input)
			add_history(input);
	//	testing(env, input);
		free(input);
	}*/
	return(0);
}
