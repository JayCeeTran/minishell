/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:35:15 by jtran             #+#    #+#             */
/*   Updated: 2025/08/26 17:01:10 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	control_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int						newline_input(char *s);
void					main_loop(t_data *data);

int	main(int ac, char **argv, char **env)
{
	t_data	data;

	(void)ac;
	(void)argv;
	data.env = env;
	data.lineno = 1;
	data.list = NULL;
	my_envp(&data);
	find_path(&data, env);
	main_loop(&data);
	free_all_exit(NULL, 0, &data, 1);
	return (0);
}

static void	input_null(t_data *data)
{
	free_split(data->path);
	free_split(data->my_env);
	free_split(data->export_list);
	exit(0);
}

void	main_loop(t_data *data)
{
	char	*input;

	input = NULL;
	while (1)
	{
		signal(SIGINT, control_c);
		signal(SIGQUIT, SIG_IGN);
		input = readline("minishell$ ");
		if (!input)
			input_null(data);
		if (newline_input(input))
			continue ;
		if (input)
			add_history(input);
		data->list = parse(input, data);
		read_list(data);
		data->lineno++;
		free(input);
	}
}

int	newline_input(char *s)
{
	if (s[0] == '\0')
		return (1);
	return (0);
}
