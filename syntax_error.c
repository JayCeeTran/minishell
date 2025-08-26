/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoale <hoale@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:56:35 by hoale             #+#    #+#             */
/*   Updated: 2025/08/26 17:02:43 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_in_quotes(int cp, char *cmd)
{
	int	i;
	int	in_sing;
	int	in_doub;

	in_sing = 0;
	in_doub = 0;
	i = 0;
	while (i <= cp)
	{
		if (!in_sing && !in_doub && cmd[i] == '\'')
			in_sing = 1;
		else if (!in_sing && !in_doub && cmd[i] == '"')
			in_doub = 1;
		else if (in_sing && cmd[i] == '\'')
			in_sing = 0;
		else if (in_doub && cmd[i] == '"')
			in_doub = 0;
		i++ ;
	}
	if (in_doub || in_sing)
		return (1);
	else
		return (0);
}

int	no_slash_n_semicol(char *cmd)
{
	int	ptr;

	if (!cmd)
		return (0);
	ptr = 0;
	while (cmd[ptr])
	{
		if ((cmd[ptr] == '\\' || cmd[ptr] == ';') && !is_in_quotes(ptr, cmd))
			return (0);
		ptr++ ;
	}
	return (1);
}
