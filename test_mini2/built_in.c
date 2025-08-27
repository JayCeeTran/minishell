/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:12:48 by jtran             #+#    #+#             */
/*   Updated: 2025/08/27 18:35:02 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_echo(t_data *data, t_cmd *cmd, int parent)
{
	int	i;
	int	nl;

	i = 1;
	nl = 1;
	(void)data;
	(void)parent;
	if (cmd->cmd[1] && ft_strcmp(cmd->cmd[1], "-n") == 0)
	{
		nl = 0;
		i++;
	}
	while (cmd->cmd[i])
	{
		ft_putstr_fd(cmd->cmd[i], 1);
		if (cmd->cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (nl)
		write(1, "\n", 1);
	return (1);
}

int	b_pwd(t_data *data, t_cmd *cmd, int parent)
{
	char	*pwd;

	(void)cmd;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		pwd = find_pwd_from_env(data, parent);
		if(!pwd)
			close_free_exit("Error: getcwd() failed.\n", 1, data, parent);
	}
	ft_putstr_fd(pwd, 1);
	free(pwd);
	write(1, "\n", 1);
	return (1);
}

int	b_env(t_data *data, t_cmd *cmd, int parent)
{
	int	i;

	i = 0;
	(void)parent;
	(void)cmd;
	while (data->my_env[i])
	{
		ft_putstr_fd(data->my_env[i], 1);
		write(1, "\n", 1);
		i++;
	}
	return (1);
}

long long validate_string(char *s, int *valid)
{
	int i;
	long long value;
	int digit;
	int sign;
	
	i = 0;
	value = 0;
	sign = 1;

	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while(s[i])
	{
		if(!ft_isdigit(s[i]))
			return(0);
		digit = s[i] - '0';
		if(value > (LLONG_MAX - digit) / 10)
				return(0);
		value = value * 10 + digit;
		i++;
	}
	if(sign == -1 && -value < LLONG_MIN)
		return(0);
	*valid = 1;
	return(sign * value);
}

int	b_exit(t_data *data, t_cmd *cmd, int parent)
{
	long long i;
	int valid;

	valid = 0;
	i = 0;
	if(cmd->cmd[1])
	{
		i = validate_string(cmd->cmd[1], &valid);
		if(!valid)
		{
			close_pipes_and_files(data, data->first);
			ft_putstr_fd("exit\nbash: exit: ", 2);
			ft_putstr_fd(cmd->cmd[1], 2);
			free_all_exit(": numeric argument required\n", 2, data, parent);
		}
		if(cmd->cmd[2])
		{
			ft_putstr_fd("bash: exit: too many arguments\n", 2);
			data->status = 1;
			return(0);
		}
		if(cmd->cmd[1])
		{
		if(i > 255 || i < 0)
			i = i % 256;
		close_pipes_and_files(data, data->first);
		free_all_exit("exit\n", i, data, parent);
		}
	}
	close_pipes_and_files(data, data->first);
	free_all_exit("exit\n", 0, data, parent);
	return (1);
}
