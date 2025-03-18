#include "minishell.h"

int	ft_strcmp(char *s, char *s2)
{
	while(*s && *s2)
	{
		if(*s != *s2)
			return(*s - *s2);
		s++;
		s2++;
	}
	return(*s - *s2);
}
