/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:38:19 by jtran             #+#    #+#             */
/*   Updated: 2025/08/27 18:47:42 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_sigint = 0;

void	control_c(int sig)
{
	(void)sig;
	g_sigint = 2;
}

int sig_hook_parent(void)
{
	if(g_sigint == 2)
	{
		rl_done = 1;
	}
	return(1);
}

int			newline_input(char *s);
void		main_loop(t_data *data);

int	main(int ac, char **argv, char **env)
{
	t_data	data;

	(void)ac;
	(void)argv;
	data.env = env;
	data.lineno = 1;
	data.list = NULL;
	data.status = 0;
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
	ft_putstr_fd("exit\n", 2);
	exit(0);
}

void	main_loop(t_data *data)
{
	char	*input;

	input = NULL;
	while (1)
	{
		rl_event_hook = sig_hook_parent;
		signal(SIGINT, control_c);
		signal(SIGQUIT, SIG_IGN);
		input = readline("minishell$ ");
		if(g_sigint == 2)
		{
			data->status = 130;
			g_sigint = 0;
			continue;
		}
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
