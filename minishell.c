#include "minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\nminishell> ", 12);
}

int	main(int ac, char **argv, char **env)
{
	char *input = NULL;
	ac++;
	argv++;
	t_data data;
	data.env = env;
	
//	signal(SIGINT, sigint_handler);
	while(1)
	{
		input = readline("minishell$ ");
		if(!input)
		{
			printf("control d\n");
			break;
		}
		if(input)
			add_history(input);
		parse_input(input, &data);
		free(input);
	}
	return(0);
}
