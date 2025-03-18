#include "minishell.h"

void	putstr_len(char *s, int fd, int len)
{
	while(len--)
	{
		write(1, s, fd);
		s++;
	}
}
