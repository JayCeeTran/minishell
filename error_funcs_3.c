#include "minishell.h"

void    close_free_exit(char *msg, int excode, t_data *data, int parent)
{
       close_pipes_and_files(data, data->first);
       free_all_exit(msg, excode, data, parent);
}

void    malloc_fail(t_data *data, char **new_env, int parent)
{
        free_split(new_env);
        close_free_exit("Error: Malloc failed!\n", 1, data, parent);
}
