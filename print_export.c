#include "minishell.h"

void	count_arguments_and_print_list(t_data *data, t_cmd *cmd, int parent)
{
	int i;

	i = 1;
	while(cmd->cmd[i])
		i++;
	if(i == 1)
		sort_my_env(data, parent);
}

void	print_export_list(char **list)
{
	int i;

	i = 0;
	while(list[i])
	{
		ft_putstr_fd("declare -x ", 1);
		print_my_env_with_quotes(list[i]);
		i++;
	}
}

void	print_my_env_with_quotes(char *s)
{
	int i;
	int quote;

	quote = 0;
	i = 0;
	while(s[i])
	{
		write(1, &s[i], 1);
		if(s[i] == '=')
		{	
			write(1, "\"", 1);
			quote = 1;
		}
		i++;
	}
	if(quote)
		write(1, "\"", 1);
	write(1, "\n", 1);
}
