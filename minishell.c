#include "minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\nminishell> ", 12);
}

int	newline_input(char *s);
void	main_loop(t_data *data);

int	main(int ac, char **argv, char **env)
{
	(void)ac;
	(void)argv;
	t_data data;
	data.env = env;
	data.lineno = 1;
	my_envp(&data);
	find_path(&data, env);
//	testing(env);
//	signal(SIGINT, sigint_handler);
	main_loop(&data);
	free_all_exit(NULL, 0, &data, 1);
	return(0);
}

void	main_loop(t_data *data)
{
	char *input;

	input = NULL;
	while(1)
	{
		input = readline("minishell$ ");
		if(!input)
		{
			printf("control d\n");
			break;
		}
		if(newline_input(input))
			continue;
		if(input)
			add_history(input); //need to clean up memory?
		data->list = parse(input, data);
	//	if(!data->list)
	//		free_all_exit(NULL, 1, data, 1);
		read_list(data);
		data->lineno++;
		free(input);
		printf("status: %d\n", data->status);
	}
}

int	newline_input(char *s)
{
	if(s[0] == '\0')
		return(1);
	return(0);	
}
