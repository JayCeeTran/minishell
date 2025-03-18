#include "minishell.h"

int	any_quotes(char *s);
void	prompt_arrow(char *s);

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
	int len;

	len = ft_strlen(s);
	if((*s == '\'' && *(s + len - 1) == '\'') || (*s == '\"' && *(s + len - 1) == '\"'))
		putstr_len(s + 1, 1, len - 2);
/*	else if((*s == '\'' && *(s + len - 1) != '\'') || (*s == '\"' && *(s + len - 1) != '\"'))
		prompt_arrow(s);*/
	else
		ft_putstr_fd(s, 1);
	return(0);
}

void	prompt_arrow(char *s)
{
	char *input;
	char c[2];

	c[0] = *s;
	c[1] = '\0';
	while(1)
	{
		input = readline("> ");
		if(!input)
			no_closing_quote();
		if(ft_strncmp(c, input, 1) == 0)
		{
			s = ft_strjoin_3(s, "\n", input + 1);
			printf("%s\n", s + 1);
			exit(1);
		}
		s = ft_strjoin_3(s, "\n", input);
	}
	printf("%s", s + 1);
}
