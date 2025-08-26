/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:43:48 by jtran             #+#    #+#             */
/*   Updated: 2025/08/26 16:24:10 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	check_max_heredoc(t_data *data, t_token *tokens)
{
	if (!below_max_heredoc(tokens))
	{
		free_token(tokens);
		free_all_exit("bash: maximum here-document count exceeded\n", 1, data,
			1);
	}
}
