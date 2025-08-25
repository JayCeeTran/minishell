#include "minishell.h"

int     is_valid_var_char(char c)
{
        return (ft_isalnum(c) || c == '_');
}
