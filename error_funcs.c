#include "minishell.h"

void	malloc_fail(char *s)
{
	ft_putstr_fd(s, 2);
	exit(1);
}
