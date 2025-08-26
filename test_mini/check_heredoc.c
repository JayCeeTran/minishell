/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:19:01 by jtran             #+#    #+#             */
/*   Updated: 2025/08/26 20:00:20 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//char	*save_heredoc_path(t_data *data, char *heredoc);
//void	heredoc_name(t_data *data, char *heredoc);
//void	print_error_msg(t_data *data, char *delimiter, int lineno);

void	write_into_heredoc(int fd, char *input, t_data *data)
{
	ft_putstr_fd(input, fd);
	write(fd, "\n", 1);
	data->lineno++;
	free(input);
}

int	input_null(char *input, t_data *data, char *file, int start_lineno)
{
	if (!input)
	{
		print_error_msg(data, file, start_lineno);
		return (1);
	}
	return (0);
}

int	compare_input_delimiter(char *input, char *delimiter, t_data *data)
{
	if (ft_strcmp(input, delimiter) == 0)
	{
		data->lineno++;
		return (1);
	}
	return (0);
}

char	*open_heredoc(int *start_lineno, char *file, int *fd, t_data *data)
{
	*start_lineno = data->lineno;
	*fd = open("heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd == -1)
		close_free_exit("Heredoc opening failed\n", 1, data, 1);
	return (file);
}

void	check_heredoc(t_redir *dir, t_data *data)
{
	char	*input;
	char	*limit;
	int		fd;
	int		start_lineno;

	while (dir)
	{
		if (dir->file && dir->redir && ft_strcmp(dir->redir, "<<") == 0)
		{
			start_lineno = data->lineno;
			limit = open_heredoc(&start_lineno, dir->file, &fd, data);
			while (1)
			{
				input = readline("> ");
				if (input_null(input, data, dir->file, start_lineno))
					break ;
				if (compare_input_delimiter(input, limit, data))
					break ;
				if (!dir->expand)
					input = expand_node(input, data);
				write_into_heredoc(fd, input, data);
			}
			close(fd);
		}
		dir = dir->next;
	}
}
