#include "minishell.h"

void	check_heredoc(t_redir *dir, t_data *data)
{
	char *input;
	char *limit;
	int	fd;
	int i;

	i = 0;
	while(dir)
	{
		if(dir->file && dir->redir)
		{
			if(ft_strcmp(dir->redir, "<<") == 0)
			{
				i++;
				limit = dir->file;
				fd = open("heredoccc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if(fd == -1)
					close_free_exit("Heredoc opening failed\n", 1, data);
				if(i == 1)
					data->heredoc_path = save_heredoc_path(data);
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
			}
		}
		if(i == 17)
			close_free_exit("-bash: maximum here-document count exceeded\n", 1, data);
		dir = dir->next;	//17 heredoccc + >, <, not tested
	}
}
