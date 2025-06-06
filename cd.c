#include "minishell.h"

int	cmd_size(t_cmd *cmd);
int	change_dir(t_data *data, t_cmd *cmd, char *opwd);
void	 change_dir_helper(t_data *data, char *opwd);
char	*new_pwd(t_data *data);

int	b_cd(t_data *data, t_cmd *cmd)
{
	char *opwd;
		
	if(cmd_size(cmd) > 2)
	{
		write(2, "-bash: cd: too many arguments\n", 30);
		data->status = 1;
		return(1);	// exit status 1??
	}
	opwd = getcwd(NULL, 0);
	if(!opwd)
	{
		close_pipes_and_files(data, data->first);
		free_all_exit("Error\ngetcwd\n", 1, data);
	}
	if(change_dir(data, cmd, opwd))
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

int	change_dir(t_data *data, t_cmd *cmd, char *opwd)
{
	if(chdir(cmd->cmd[1]) == 0)
		change_dir_helper(data, opwd);
	else
	{
		cd_nsf(cmd->cmd[1]); //can it return 1 on something else too?
		data->status = 1;//maybe add exit status??
	}
	free(opwd);
	return(1);
}

void change_dir_helper(t_data *data, char *opwd)
{
	int check1;
	int check2;
	int i;

	i = 0;
	check1 = 0;
	check2 = 0;
	while(data->my_env[i])
	{
		if(!check1 && ft_strncmp("PWD=", data->my_env[i], 4) == 0)
		{
			free(data->my_env[i]);
			data->my_env[i] = new_pwd(data);
			check1 = 1;
		}
		else if(!check2 && ft_strncmp("OLDPWD=", data->my_env[i], 7) == 0)
		{
			free(data->my_env[i]);
			data->my_env[i] = ft_strjoin("OLDPWD=", opwd);
			check2 = 1;
		}
		if(check1 && check2)
			break;
		i++;
	}
}

char	*new_pwd(t_data *data)
{
	char *pwd;
	char *dest;

	pwd = getcwd(NULL, 0);
	if(!pwd)
	{
		close_pipes_and_files(data, data->first);
		free_all_exit("Error\ngetcwd\n", 1, data);
	}
	dest = ft_strjoin("PWD=", pwd);
	free(pwd);
	return(dest);
}
