#include "minishell.h"

char **reparse(char **cmd, t_data *data)
{
	int i;
	int j;

	i = 1;
	while(cmd[i])
	{
		j = 0;
		if(cmd[i][j] != '\'')
		{
			while(cmd[i][j])
			{
				if(cmd[i][j] == '$')
					j = expand_var(cmd[i], j, data);
				j++;
			}
		}
		i++;
	}
	return(NULL);
}

int	expand_var(char *s, int j, t_data *data)
{
	char dest[100];
	int i;
	char *val;

	i = 0;
	j++;
	(void)data;
	while(s[j] && s[j] != ' ')
		dest[i++] = s[j++];
	dest[i] = '\0';
	val = getenv(dest);
	if(val)
		printf("%s\n", val);
	return(j);
}
