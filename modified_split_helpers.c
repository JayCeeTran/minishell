#include "minishell.h"

int	single_quote(const char *str, int *i)
{
	int j;

	if(str[(*i)] == '\'')
	{
		j = 1;
		while(str[(*i) + j] && str[(*i) + j] != '\'')
			j++;
		if(!str[(*i) + j])
			no_closing_quote();
		if(j != 1)
		{
			*i = *i + j + 1;
			return(1);
		}
		else if(str[(*i)] == '\'' && str[(*i) + j] == '\'')
		{
			(*i) += 2;
			return(1);
		}
	}
	return(0);
}

int	single_quote_dup(const char **str, char **tokens, int *j)
{
	int poscount;

	if(**str == '\'')
	{
		poscount = 1;
		while(*(*str + poscount) && *(*str + poscount) != '\'')
			poscount++;
		if(poscount != 1)
		{
			tokens[(*j)] = ft_substr(*str, 0, poscount + 1);
			if(!tokens[(*j)++])
				free_tokens(tokens, (*j) - 1); // exit needed
			*str += poscount + 1;
			return(1);
		}
		else if(**str == '\'' && *(*str + 1) == '\'')
		{
			tokens[(*j)] = malloc(1);
			if(!tokens[(*j)])
				free_tokens(tokens, (*j));
			tokens[(*j)++][0] = '\0';
			*str += 2;
			return(1);
		}
	}
	return(0);
}

int	double_quote(const char *str, int *i)
{
	int j;

	if(str[(*i)] == '\"')
	{
		j = 1;
		while(str[(*i) + j] && str[(*i) + j] != '\"')
			j++;
		if(!str[(*i) + j])
			no_closing_quote();
		if(j != 1)
		{
			*i = *i + j + 1;
			return(1);
		}
		else if(str[(*i)] == '\"' && str[(*i) + j] == '\"')
		{
			(*i) += 2;
			return(1);
		}
	}
	return(0);
}

int	double_quote_dup(const char **str, char **tokens, int *j)
{
	int poscount;

	if(**str == '\"')
	{
		poscount = 1;
		while(*(*str + poscount) && *(*str + poscount) != '\"')
			poscount++;
		if(poscount != 1)
		{
			tokens[(*j)] = ft_substr(*str, 0, poscount + 1);
			if(!tokens[(*j)++])
				free_tokens(tokens, (*j) - 1); // exit needed
			*str += poscount + 1;
			return(1);
		}
		else if(**str == '\"' && *(*str + 1) == '\"')
		{
			tokens[(*j)] = malloc(1);
			if(!tokens[(*j)])
				free_tokens(tokens, (*j));
			tokens[(*j)++][0] = '\0';
			*str += 2;
			return(1);
		}
	}
	return(0);
}


