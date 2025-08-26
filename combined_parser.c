/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combined_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoale <hoale@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 10:43:09 by hoale             #+#    #+#             */
/*   Updated: 2025/08/26 14:01:20 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_closed_quotes(char *cmd)
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

static int	valid_redirs(t_token *tokens)
{
	t_token	*ptr;

	while (tokens)
	{
		if (tokens->is_op == 1 && ft_strncmp(tokens->token, "|", 2) != 0)
		{
			ptr = tokens->next;
			while (ptr && ptr->is_op == 3)
				ptr = ptr->next;
			if (!ptr || ptr->is_op == 1)
				return (0);
		}
		tokens = tokens->next;
	}
	return (1);
}

static int	valid_pipes(t_token *tokens)
{
	t_token	*cur;
	t_token	*last_pipe;
	t_token	*seg_start;

	cur = tokens;
	last_pipe = NULL;
	while (cur)
	{
		if (cur->is_op == 1 && !ft_strncmp(cur->token, "|", 2))
		{
			if (last_pipe)
				seg_start = last_pipe->next;
			else
				seg_start = tokens;
			if (is_empty_segment(seg_start, cur))
				return (0);
			last_pipe = cur;
		}
		cur = cur->next;
	}
	if (last_pipe && is_empty_segment(last_pipe->next, NULL))
		return (0);
	return (1);
}

static int	below_max_heredoc(t_token *tokens)
{
	t_token	*ptr;
	int		count_heredoc;

	ptr = tokens;
	count_heredoc = 0;
	while (ptr->next)
	{
		if (ptr->is_op == 1 && ft_strncmp(ptr->token, "<<", 3) == 0)
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

	if (is_closed_quotes(line) == 0)
		return (write(2, "Error1\n", 7), NULL);
	tokens = tokenize(line);
	if (!tokens)
		return (NULL);
	if(!below_max_heredoc(tokens))
        {
                free_all_exit("bash: maximum here-document count exceeded\n", 1, data, 1);
                return(NULL);
        }
	if (!valid_redirs(tokens) || !valid_pipes(tokens))
	{
		free_token(tokens);
		return (write(2, "Error2\n", 7), NULL);
	}
	expand_token(&tokens, data);
	simplify_tokens(&tokens);
	cmd_list = parse_cmd_list(tokens);
	free_token(tokens);
	if (!cmd_list)
		return (NULL);
	return (cmd_list);
}
