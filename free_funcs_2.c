#include "minishell.h"

void    free_list(t_data *data)
{
        t_cmd *cur;

        while(data->list)
        {
                cur = data->list;
                data->list = data->list->next;
                free_split(cur->cmd);
                free_redir(cur->redirections);
                free(cur);
        }
        data->list = NULL;
}

void    free_token(t_token *token)
{
        t_token *temp;
        while(token)
        {
                temp = token;
                token = token->next;
                free(temp->token);
                free(temp);
        }
}

void    free_redir(t_redir *directs)
{
        t_redir *cur;

        while(directs)
        {
                cur = directs;
                directs = directs->next;
                free(cur->redir);
                free(cur->file);
                free(cur);
        }
}

char    *ft_strjoin_free(char *s1, char *s2)
{
        char    *res;

        res = ft_strjoin(s1, s2);
        free(s1);
        return (res);
}
