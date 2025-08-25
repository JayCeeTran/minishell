#include "minishell.h"

static int is_closed_quotes(char *cmd)
{
	int		is_closed;
	char	*ptr;
	char	quote;

	is_closed = 0;
	ptr = cmd;
	quote = 'a';
	while (*ptr)
	{
		if ((*ptr == '\'' || *ptr == '\"') && quote == 'a')
		{
			is_closed++ ;
			quote = *ptr;
		}
		else if ((*ptr == quote && quote != 'a'))
		{
			is_closed++ ;
			quote = 'a';
		}
			ptr++ ;
	}
	if (is_closed % 2 == 0)
		return (1);
	else
		return (0);
}

static int valid_redirs(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->is_operator == 1 && ft_strncmp(tokens->token, "|", 2) != 0)
		{
			if (!tokens->next || tokens->next->is_operator == 1)
				return (0);
		}
		tokens = tokens->next;
	}
	return (1);
}

//Check if there is no pipe operator at begin and the end of the list
static int no_pipe_edges(t_token *tokens)
{
	t_token	*last;

	if (tokens->is_operator == 1 && !ft_strncmp(tokens->token, "|", 2))
		return (0);
	last = tokens;
	while (last->next)
		last = last->next;
	if (last->is_operator == 1 && !ft_strncmp(last->token, "|", 2))
		return (0);
	return (1);
}

static int below_max_heredoc(t_token *tokens)
{
	t_token	*ptr;
	int		count_heredoc;

	ptr = tokens;
	count_heredoc = 0;
	while (ptr->next)
	{
		if (ptr->is_operator == 1 && ft_strncmp(ptr->token, "<<", 3) == 0)
			count_heredoc++ ;
		ptr = ptr->next;
	}
	if (count_heredoc > 16)
		return (0);
	else
		return (1);
}

t_cmd	*parse(char *line, t_data *data)
{
	t_token	*tokens;
	t_cmd	*cmd_list;

	if(is_closed_quotes(line) == 0)
		return(write(2, "Error1\n", 7), NULL);
	tokens = tokenize(line);
	if(!below_max_heredoc(tokens))
	{
        	ft_putstr_fd("bash: maximum here-document count exceeded\n", 2)    ;
		free_all_exit("bash: maximunm here-document count exceeded\n", 1, data, 1);
		return(NULL);
	}		
	if (!valid_redirs(tokens) || !no_pipe_edges(tokens))
	{
		free_token(tokens);
		return(write(2, "Error2\n", 7), NULL);
	}
	expand_token(&tokens, data);
	simplify_tokens(&tokens);
	cmd_list = parse_cmd_list(tokens);
	return (cmd_list);
}
