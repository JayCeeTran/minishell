#include "minishell.h"

void	free_tokens_all_exit(char *s, t_token *tokens, t_data *data)
{
	free_token(tokens);
	free_all_exit(s, 1, data, 0);
}
