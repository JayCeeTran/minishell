#include "minishell.h"

char *ft_strjoin_3(char *s, char *s2, char *s3)
{
	int len;
	char *dest;
	int i;

	i = 0;
	len = ft_strlen(s) + ft_strlen(s2) + ft_strlen(s3);
	dest = malloc(len + 1);
	while(*s)
		dest[i++] = *s++;
	while(*s2)
		dest[i++] = *s2++;
	while(*s3)
		dest[i++] = *s3++;
	dest[i] = '\0';
	return(dest);
}
