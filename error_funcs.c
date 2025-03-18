#include "minishell.h"

void	err_msg_exit(char *s)
{
	ft_putstr_fd(s, 2);
	exit(1);
}

void	no_closing_quote(void)
{
	ft_putstr_fd("Error\nNo closing quotes\n", 2);
	exit(1);
}
