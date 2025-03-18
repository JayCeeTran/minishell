#include "minishell.h"

void	compare_inputs(char **command);

void	parse_input(char *s, t_data *data)
{
	char **command;

	command = mod_split(s, ' ');
	if(!command)
		malloc_fail("Error\nMalloc failed.\n");
	reparse(command, data);
	compare_inputs(command);
	/*for(int i = 0; command[i]; i++)
	{
		printf("%s\n", command[i]);
	}*/

}

void	compare_inputs(char **command)
{
	if(ft_strcmp(command[0], "exit") == 0)
		exit_cmd(command);
	else if(ft_strcmp(command[0], "echo") == 0)
		echo_cmd(command);
/*	else if(ft_strcmp(command[0], "cd") == 0)
		cd_cmd(command);
	else if(ft_strcmp(command[0], "pwd") == 0)
		pwd_cmd(command);
	else if(ft_strcmp(command[0], "export") == 0);
		export_cmd(command);
	else if(ft_strcmp(command[0], "unset") == 0);
		unset_cmd(command);
	else if(ft_strcmp(command[0], "env") == 0);
		env_cmd(commmad);
*/
}
