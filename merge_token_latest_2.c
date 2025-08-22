#include "minishell.h"

static char *strjoin_free(char *s1, const char *s2)
{
    size_t len1 = ft_strlen(s1);
    size_t len2 = ft_strlen(s2);
    char *res = malloc(len1 + len2 + 1);
    if (!res)
        return NULL;
    ft_memcpy(res, s1, len1);
    ft_memcpy(res + len1, s2, len2);
    res[len1 + len2] = '\0';
    free(s1);
    return res;
}

static void merge_tokens(t_token *head)
{
    t_token *cur = head;

    while (cur && cur->next)
    {
        if ((cur->is_operator != 1 && cur->is_operator != 3) 
            && (cur->next->is_operator != 1 && cur->next->is_operator != 3))
        {
            cur->token = strjoin_free(cur->token, cur->next->token);
            t_token *tmp = cur->next;
            cur->next = tmp->next;
            free(tmp->token);
            free(tmp);
            continue;
        }
        cur = cur->next;
    }
}

static void remove_space(t_token **head)
{
    t_token *cur = *head;
    t_token *prev = NULL;

    while (cur)
    {
        if (cur->is_operator == 3 && ft_strncmp(cur->token, " ", 2) == 0)
        {
            t_token *tmp = cur;
            if (prev)
                prev->next = cur->next;
            else
                *head = cur->next;
            cur = cur->next;
            free(tmp->token);
            free(tmp);
            continue;
        }
        prev = cur;
        cur = cur->next;
    }
}

void simplify_tokens(t_token **head)
{
    merge_tokens(*head);
    remove_space(head);
}
