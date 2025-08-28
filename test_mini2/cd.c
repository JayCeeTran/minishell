/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:16:02 by jtran             #+#    #+#             */
/*   Updated: 2025/08/27 13:55:23 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		cmd_size(t_cmd *cmd);
int		change_dir(t_data *data, t_cmd *cmd, char *opwd, int parent);
void	change_dir_helper(t_data *data, char *opwd, int parent);
char	*new_pwd(t_data *data, int parent, char *opwd, int index);

int	b_cd(t_data *data, t_cmd *cmd, int parent)
{
	char	*opwd;

	if (cmd_size(cmd) > 2)
	{
		write(2, "-bash: cd: too many arguments\n", 30);
		data->status = 1;
		return (0);
	}
	opwd = getcwd(NULL, 0);
	if (!opwd)
	{
		opwd = find_pwd_from_env(data, parent);
		if(!opwd)
			close_free_exit("Error: getcwd() failed.\n", 1, data, parent);
	}
	if (change_dir(data, cmd, opwd, parent))
		return (1);
	return (0);
}

int	cmd_size(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd[i])
		i++;
	return (i);
}

int	change_dir(t_data *data, t_cmd *cmd, char *opwd, int parent)
{
	int	status_changed;
	int	error;

	status_changed = 0;
	error = cd_home(data, cmd, opwd, parent);
	cd_error_msg(data, cmd, error, &status_changed);
	free(opwd);
	if (status_changed)
		return (0);
	return (1);
}

void	change_dir_helper(t_data *data, char *opwd, int parent)
{
	int	check1;
	int	check2;
	int	i;

	i = 0;
	check1 = 0;
	check2 = 0;
	create_pwd_if_doesnt_exist(data, parent);
	while (data->my_env[i])
	{
		if (!check1)
			check1 = find_pwd(data, parent, opwd, &i);
		else if (!check2)
			check2 = find_oldpwd(data, parent, opwd, &i);
		if (check1 && check2)
			break ;
		i++;
	}
}

char	*new_pwd(t_data *data, int parent, char *opwd, int index)
{
	char	*pwd;
	char	*dest;
	int		env_size;
	int		exit;
	(void)parent;
	(void)index;
	
	env_size = envp_size(data->my_env);
	(void)env_size;
	exit = 0;
	(void)opwd;
	dest = NULL;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		exit = 1;
	if (!exit)
		dest = ft_strjoin("PWD=", pwd);
	if (!dest || exit)
	{
		free(pwd);
		make_my_env_freeable(data, opwd, index, env_size);
		close_free_exit("Error: Malloc failed!\n", 1, data, parent);
	}
	free(pwd);
	return (dest);
}
