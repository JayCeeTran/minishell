/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:28:16 by jtran             #+#    #+#             */
/*   Updated: 2025/08/26 19:28:30 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_export_list(void);

void	create_opwd_pwd(t_data *data)
{
	char **my_env;
	char *cwd;
	char *pwd;

	cwd = getcwd(NULL, 0);
	if(!cwd)
		err_msg_exit("Error: Malloc Failed!\n", 1);
	pwd = ft_strjoin("PWD=", cwd);
	free(cwd);
	if(!pwd)
		err_msg_exit("Error: Malloc Failed\n", 1);
	my_env = malloc(3 * sizeof(char *));
	if(!my_env)
	{
		free(pwd);
		err_msg_exit("Error: Malloc Failed!\n", 1);
	}
	my_env[0] = ft_strdup(pwd);
	free(pwd);
	if(!my_env[0])
	{
		free(my_env);
		err_msg_exit("Error: Malloc Failed!\n", 1);
	}
/*	my_env[1] = ft_strdup("OLDPWD=");
	if(!my_env[1])
	{
		free(my_env[0]);
		free(my_env);
		err_msg_exit("Error: Malloc Failed!\n", 1);
	}
*/	my_env[1] = NULL;
	data->my_env = my_env;
	data->export_list = create_export_list();
}

void	my_envp(t_data *data)
{
	int		env_size;
	char	**my_env;
	int		i;

	if(!data->env[0])
	{	
		create_opwd_pwd(data);
		return;
	}
	else
		env_size = envp_size(data->env);
	my_env = malloc((env_size + 2) * sizeof(char *));
	if(!my_env)
		err_msg_exit("Error: Malloc Failed!\n", 1);
	i = 0;
	while (i < env_size)
	{
		my_env[i] = ft_strdup(data->env[i]);
		if (!my_env[i])
		{
			free_split(my_env);
			err_msg_exit("Error: Malloc Failed!\n", 1);
		}
		i++;
	}
	my_env[i] = NULL;
	data->my_env = my_env;
	data->export_list = create_export_list();
}

char	**create_export_list(void)
{
	char	**temp;

	temp = malloc(sizeof(char *));
	temp[0] = NULL;
	return (temp);
}

int	envp_size(char **env)
{
	int	count;

	count = 0;
	while (env[count])
		count++;
	return (count);
}
