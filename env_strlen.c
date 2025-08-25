#include "minishell.h"

int	env_strlen(char *s)
{
	int i;

	i = 0;
	while(s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	if(s[i] == '=')
		return(i);
	if(s[i] == '\0')
		return(-3);
	return(-2);
}	
