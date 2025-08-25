#include "minishell.h"

int	fork_heredoc(t_data *data, t_cmd *cmd)
{
	pid_t pid;
	int status;

	pid = fork();
	if(pid == -1)
	{
		close_pipes_and_files(data, data->first);
		free_all_exit("Error\nFork Failed\n", 1, data, 1);
	}
	if(pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		check_heredoc(cmd->redirections, data);
		exit(0);
	}
	waitpid(pid, &status, 0);
	if(WIFSIGNALED(status))
	{
		data->status = 128 + WTERMSIG(status);
		write(2, "\n", 1);
		return(1);
	}
	else if(WIFEXITED(status))
		data->status = WEXITSTATUS(status);
	return(0);
}
