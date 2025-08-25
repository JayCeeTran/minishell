#include "minishell.h"

void    no_such_file(char *file)
{
        write_bash();
        ft_putstr_fd(file, 2);
        ft_putstr_fd(": No such file or directory\n", 2);
}

void    cd_nsf(char *file)
{
        write_bash();
        write(2, "cd: ", 4);
        ft_putstr_fd(file, 2);
        ft_putstr_fd(": No such file or directory\n", 2);
}

void    no_permission(char *file)
{
        write_bash();
        ft_putstr_fd(file, 2);
        ft_putstr_fd(": Permission denied\n", 2);
}

void    command_not_found(t_cmd *cmd, t_data *data)
{
        ft_putstr_fd(cmd->cmd[0], 2);
        close_free_exit(": command not found\n", 127, data, 0);
}

void    export_error(char *s)
{
        write_bash();
        write(2, "export: ", 8);
        ft_putstr_fd(s, 2);
        ft_putstr_fd(": not a valid identifier\n", 2);
}
