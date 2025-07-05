#include "minishell.h"

char *save_heredoc_path(t_data *data, char *heredoc);
void	heredoc_name(t_data *data, char *heredoc);

void	check_heredoc(t_redir *dir, t_data *data)
{
	char *input;
	char *limit;
	int	fd;
	char heredoc[20];

	while(dir)
	{
		if(dir->file && dir->redir && ft_strcmp(dir->redir, "<<") == 0)
		{
			heredoc_name(data, heredoc);
			limit = dir->file;
			fd = open(heredoc, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if(fd == -1)
				close_free_exit("Heredoc opening failed\n", 1, data, 1);
			data->heredoc->path[data->heredoc->count] = save_heredoc_path(data, heredoc);
			while(1)
			{
				input = readline("> ");
				if(ft_strcmp(input, limit) == 0)
					break;
				ft_putstr_fd(input, fd);
				write(fd, "\n", 1);
				free(input);
			}
			close(fd);
			data->heredoc->count++;
		}
		if(data->heredoc->count == 17)
			close_free_exit("-bash: maximum here-document count exceeded\n", 1, data, 1);
		dir = dir->next;	//17 heredoccc + >, <, not tested
	}
}

void	heredoc_name(t_data *data, char *heredoc)
{
	char *temp;
	char *number;

	number = ft_itoa(data->heredoc->count);	
	if(!number)
		close_free_exit("Malloc failed!\n", 1, data, 1);
	temp = ft_strjoin("heredoc_", number);
	if(!temp)
	{
		free(number);
		close_free_exit("Malloc failed!\n", 1, data, 1);
	}
	ft_strlcpy(heredoc, temp, 20);
	free(temp);
	free(number);
}

char *save_heredoc_path(t_data *data, char *heredoc)
{
        char *here_path;
        char *cwd = getcwd(NULL, 0);
        if(!cwd)
                close_free_exit("Error\nHeredoc path.\n", 1, data, 1);
        here_path = ft_strjoin_3(cwd, "/", heredoc);
        free(cwd);
        return(here_path);
}
