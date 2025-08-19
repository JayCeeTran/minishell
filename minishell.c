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
	t_data data;
	data.env = env;
	my_envp(&data);
	find_path(&data, env);
//	testing(env);
//	signal(SIGINT, sigint_handler);
	while(1)
	{
		input = readline("minishell$ ");
		if(!input)
		{
			printf("control d\n");
			break;
		}
//		if(newline_input)

		if(input)
			add_history(input); //need to clean up memory?
		data.list = parse(input, data.my_env);
	//	free_token(token);
		read_list(&data);
		free(input);
		printf("status: %d\n", data.status);
	}
	free_all_exit(NULL, 0, &data, 1);
	return(0);
}
