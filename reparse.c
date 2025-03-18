#include "minishell.h"

char	*expand_var(char *s, int *j, t_data *data);
char *new_string(char *s, char *val, int len);

char **reparse(char **cmd, t_data *data)
{
	int i;
	int j;
	char *dest;
	
	(void)data;
	i = 1;
	while(cmd[i])
	{
		j = 0;
		if(cmd[i][j] != '\'')
		{
			while(cmd[i][j])
			{
				if(cmd[i][j] == '$')
				{
					dest = expand_var(cmd[i], &j, data);
					free(cmd[i]);
					cmd[i] = dest;
					printf("%s DEST\n", dest);
					printf("%d JJJJ\n", j);
				}	
				j++;
			}
		}
		i++;
	}
	return(NULL);
}

char *expand_var(char *s, int *j, t_data *data)
{
	char dest[100];
	int i;
	char *val;

	i = 0;
	(*j)++;
	(void)data;
	while(s[(*j)] && s[(*j)] != ' ' && s[(*j)] != '\"')
		dest[i++] = s[(*j)++];
	dest[i] = '\0';
	val = getenv(dest);
/*	if(val)
		printf("%s\n", val);*/
	*j = *j - i - 2 + ft_strlen(val);
	return(new_string(s, val, i));
	
}

char *new_string(char *s, char *val, int len)
{
	int i;
	int j;
	char *dest;
	int flag;

	dest = malloc(ft_strlen(s) + (ft_strlen(val)));
	i = 0;
	j = 0;
	flag = 0;
	while(s[i])
	{
		if(s[i] == '$' && !flag)
		{
			flag = 1;
			while(*val)
				dest[j++] = *val++;
			i += len + 1;
			continue;
		}
		dest[j++] = s[i++];
	}
	dest[j] = '\0';
	return(dest);
}
