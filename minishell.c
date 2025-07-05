#include "minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\nminishell> ", 12);
}

int	main(int ac, char **argv, char **env)
{
	char *input = NULL;
	(void)ac;
	(void)argv;
//	testing(env);
//	env++;
	t_data data;
	data.env = env;
	my_envp(&data);
	find_path(&data, env);
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
	//	testing(env, input);
		data.list = parse_cmd_list(tokenize(input));
		read_list(&data);
		free(input);
	}
	return(0);
}
