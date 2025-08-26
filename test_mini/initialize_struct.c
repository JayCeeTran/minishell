/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:26:33 by jtran             #+#    #+#             */
/*   Updated: 2025/08/26 19:26:38 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_struct(t_built_ins *built_ins)
{
	built_ins[0].name = "echo";
	built_ins[0].func = b_echo;
	built_ins[1].name = "pwd";
	built_ins[1].func = b_pwd;
	built_ins[2].name = "env";
	built_ins[2].func = b_env;
	built_ins[3].name = "export";
	built_ins[3].func = b_export;
	built_ins[4].name = "unset";
	built_ins[4].func = b_unset;
	built_ins[5].name = "exit";
	built_ins[5].func = b_exit;
	built_ins[6].name = "cd";
	built_ins[6].func = b_cd;
	built_ins[7].name = NULL;
	built_ins[7].func = NULL;
}
