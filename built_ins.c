#include "minishell.h"

int	any_quotes(char *s);


void	exit_cmd(char **cmd)
{
	free_split(cmd);
	exit(0);
}

void	echo_cmd(char **cmd)
{
	int i;
	int nl;

	i = 1;
	nl = 1;
	if(cmd[1] && ft_strcmp(cmd[1], "-n") == 0)
	{
		nl = 0;
		i++;
	}
	while(cmd[i])
	{
		any_quotes(cmd[i]);	
		if(cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if(nl)
		write(1, "\n", 1);
}

int	any_quotes(char *s)
{
	if(*s == '\'' && *(s + ft_strlen(s) - 1) == '\'')
	{
		putstr_len(s + 1, 1, ft_strlen(s) - 2);
	}
	else if(*s == '\"' && *(s + ft_strlen(s) - 1) == '\"')
	{
		putstr_len(s + 1, 1, ft_strlen(s) - 2);
	}
	else
		ft_putstr_fd(s, 1);
	return(0);
}
