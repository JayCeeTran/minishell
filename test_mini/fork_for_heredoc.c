/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_for_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:25:22 by jtran             #+#    #+#             */
/*   Updated: 2025/08/26 19:35:26 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_program(t_data *data)
{
	close_pipes_and_files(data, data->first);
	free_all_exit("Error\nFork Failed\n", 1, data, 1);
}

void	prompt_heredoc(t_data *data, t_redir *redir)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	check_heredoc(redir, data);
	free_all_exit(NULL, 0, data, 0);
}

int	was_there_a_signal(t_data *data, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		data->status = 128 + WTERMSIG(status);
		write(2, "\n", 1);
		return (1);
	}
	else if (WIFEXITED(status))
		data->status = WEXITSTATUS(status);
	return (0);
}

int	fork_heredoc(t_data *data, t_cmd *cmd)
{
	pid_t	pid;
	t_redir	*cur;
	int		check;

	check = 0;
	cur = cmd->redirs;
	while (cur)
	{
		if (!check && ft_strcmp(cur->redir, "<<") == 0)
		{
			signal(SIGINT, SIG_IGN);
			pid = fork();
			if (pid == -1)
				exit_program(data);
			if (pid == 0)
				prompt_heredoc(data, cur);
			if (was_there_a_signal(data, pid))
				return (1);
			check = 1;
			signal(SIGINT, SIG_DFL);
		}
		cur = cur->next;
	}
	return (0);
}
