/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:52:48 by jtran             #+#    #+#             */
/*   Updated: 2025/08/26 19:52:50 by jtran            ###   ########.fr       */
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
