#include "minishell.h"

int	cmd_size(t_cmd *cmd);
int	change_dir(t_data *data, t_cmd *cmd, char *opwd, int parent);
void	 change_dir_helper(t_data *data, char *opwd, int parent);
char	*new_pwd(t_data *data, int parent, char *opwd, int index);
void	make_my_env_freeable(t_data *data, char *opwd, int index, int env_size);
void	find_home_from_my_env(t_data *data, char **home);

int	b_cd(t_data *data, t_cmd *cmd, int parent)
{
	char *opwd;
		
	if(cmd_size(cmd) > 2)
	{
		write(2, "-bash: cd: too many arguments\n", 30);
		data->status = 1;
		return(0);	// exit status 1??
	}
	opwd = getcwd(NULL, 0);
	if(!opwd)
		close_free_exit("Error: getcwd() failed.\n", 1, data, parent);
	if(change_dir(data, cmd, opwd, parent))
		return(1);
	return(0);
}

int	cmd_size(t_cmd *cmd)
{
	int i;

	i = 0;
	while(cmd->cmd[i])
		i++;
	return(i);
}

int	change_dir(t_data *data, t_cmd *cmd, char *opwd, int parent)
{
	int status_changed;
	char *home;
	int error;

	error = 0;
	home = NULL;
	status_changed = 0;
	if(!cmd->cmd[1])
	{
		find_home_from_my_env(data, &home);
		if(chdir(home) == 0)
			change_dir_helper(data, opwd, parent);
		else
			error = 1;
	}
	else if(cmd->cmd[1] && chdir(cmd->cmd[1]) == 0)
		change_dir_helper(data, opwd, parent);
	else
		error = 1;
	if(error)
	{
		write_bash();
		write(2, "cd: ", 4);
		if(cmd->cmd[1])
			ft_putstr_fd(cmd->cmd[1], 2);
		write(2, ": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 1);
		data->status = 1;
		status_changed = 1;
	}
	free(opwd);
	if(home)
		free(home);
	if(status_changed)
		return(0);
	return(1);
}

void change_dir_helper(t_data *data, char *opwd, int parent)
{
	int check1;
	int check2;
	int i;
	int env_size;

	i = 0;
	check1 = 0;
	check2 = 0;
	env_size = envp_size(data->my_env);
	while(data->my_env[i])
	{
		if(!check1 && ft_strncmp("PWD=", data->my_env[i], 4) == 0)
		{
			free(data->my_env[i]);
			data->my_env[i] = new_pwd(data, parent, opwd, i);
			check1 = 1;
		}
		else if(!check2 && ft_strncmp("OLDPWD=", data->my_env[i], 7) == 0)
		{
			free(data->my_env[i]);
			data->my_env[i] = ft_strjoin("OLDPWD=", opwd);
			if(!data->my_env[i])
			{
				make_my_env_freeable(data, opwd, i, env_size);
				close_free_exit("Error: Malloc failed!\n", 1, data, parent);
			}
			check2 = 1;
		}
		if(check1 && check2)
			break;
		i++;
	}
}

char	*new_pwd(t_data *data, int parent, char *opwd, int index)
{
	char *pwd;
	char *dest;
	int env_size;
	int exit;

	env_size = envp_size(data->my_env);
	exit = 0;
	pwd = getcwd(NULL, 0);
	if(!pwd)
		exit = 1;
	if(!exit)
		dest = ft_strjoin("PWD=", pwd);
	if(exit || !dest)
	{
		free(pwd);
		make_my_env_freeable(data, opwd, index, env_size);
		close_free_exit("Error: Malloc failed!\n", 1, data, parent);
	}
	free(pwd);
	return(dest);
}

void	make_my_env_freeable(t_data *data, char *opwd, int index, int env_size)
{
	free(opwd);
	data->my_env[index] = NULL;
	free_split_index(data->my_env, env_size);
	data->my_env = NULL;
}

void	find_home_from_my_env(t_data *data, char **home)
{
	int i;

	i = 0;
	while(data->my_env[i])
	{
		if(ft_strncmp(data->my_env[i], "HOME=", 5) == 0)
			*home =ft_substr(data->my_env[i], 5, 200);
		i++;
	}
	
}
