#include "minishell.h"

char *save_heredoc_path(t_data *data, char *heredoc);
void	heredoc_name(t_data *data, char *heredoc);
char 	*expand_input(char *input, char **envp);
void	print_error_msg(t_data *data, char *delimiter, int lineno);

void	check_heredoc(t_redir *dir, t_data *data)
{
	char *input;
	char *limit;
	int	fd;
	char heredoc[20];
	int start_lineno;

	while(dir)
	{
		if(dir->file && dir->redir && ft_strcmp(dir->redir, "<<") == 0)
		{	
			start_lineno = data->lineno;
			heredoc_name(data, heredoc);
			limit = dir->file;
			fd = open(heredoc, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if(fd == -1)
				close_free_exit("Heredoc opening failed\n", 1, data, 1);
			data->heredoc->path[data->heredoc->count] = save_heredoc_path(data, heredoc);
			while(1)
			{
				input = readline("> ");
				if(!input)
				{
					print_error_msg(data, dir->file, start_lineno);
					break;
				}
				if(ft_strcmp(input, limit) == 0)
				{
					data->lineno++;
					break;
				}
				if(has_dollar(input))
					input = expand_input(input, data->my_env);
				ft_putstr_fd(input, fd);
				write(fd, "\n", 1);
				data->lineno++;
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

char 	*expand_input(char *input, char **envp)
{
	int i;
	char *result;

	i = 0;
	result = ft_strdup(""); //malloc error exit
//	if(!result)
//		close_free_exit("Error: Malloc failed!", 1, data, 1);
        while (input[i])
        {
	        if (input[i] == '$' && input[i + 1])
                {
                     	int   start = ++i; //move declaration outside of the loop
                        while (input[i] && is_valid_var_char(input[i]))
                                i++;
                        char    *key = ft_substr(input, start, i - start);
                        char    *val = get_env_value(key, envp); // same and malloc error exit
                        result = ft_strjoin_free(result, val); // malloc error exit
                        free(key);
                        i--;
                }
                else
                        append_char(&result, input[i]);
                i++;
        }
	free(input);
        return (result);
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
        char *cwd;

	cwd = getcwd(NULL, 0);
        if(!cwd)
                close_free_exit("Error\nHeredoc path.\n", 1, data, 1);
        here_path = ft_strjoin_3(cwd, "/", heredoc);
        free(cwd);
        return(here_path);
}

void	print_error_msg(t_data *data, char *delimiter, int lineno)
{
	(void)data;
         ft_putstr_fd("bash: warning: here-document at line ", 2);
         ft_putnbr_fd(lineno, 2);
         ft_putstr_fd(" delimited by end-of-file (wanted '", 2);
	 ft_putstr_fd(delimiter, 2);
	 ft_putstr_fd("')", 2);
	 write(2, "\n", 1);
}
