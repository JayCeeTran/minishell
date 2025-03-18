#include "minishell.h"

static size_t	word_count(const char *str, char c)
{
	size_t	count;
	int i;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i])
			count++;
		if(single_quote(str, &i) || double_quote(str, &i))
			continue;
		while (str[i] != c && str[i])
		{
			if(str[i] == '\'' || str[i] == '\"')
					break;
			i++;
		}
	}
	return (count);
}

char	**free_tokens(char **arr, int j)
{
	while (j > 0)
		free (arr[--j]);
	free (arr);
	return (NULL);
}

static char	**dutty(char **arr, int j)
{
	arr[j] = NULL;
	return (arr);
}

char	**mod_split(const char *str, char c)
{
	size_t	words;
	char	**tokens;
	int		j;
	int		poscount;

	j = 0;
	words = word_count(str, c);
	printf("%ld wordcount\n", words);
	tokens = malloc((words + 1) * sizeof(char *));
	if (!tokens || !str)
		return (NULL);
	while (*str && words-- > 0)
	{
		poscount = 0;
		while (*str == c && *str)
			str++;
		if(single_quote_dup(&str, tokens, &j) || double_quote_dup(&str, tokens, &j))
			continue;
		while (*str && *str != c)
		{	
			if(*str == '\'' || *str == '\"')
					break;
			str++;
			poscount++;
		}
		tokens[j] = ft_substr(str - poscount, 0, poscount);
		if (!tokens[j++])
			return (free_tokens(tokens, j - 1));
	}
	return (dutty(tokens, j));
}
