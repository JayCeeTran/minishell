#include "minishell.h"

char *save_heredoc_path(t_data *data)
{
	char *here_path;
	char *cwd = getcwd(NULL, 0);
	if(!cwd)
		close_free_exit("Error\nHeredoc path.\n", 1, data);
	here_path = ft_strjoin(cwd, "/heredoccc");
	free(cwd);
	return(here_path);
}
