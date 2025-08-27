#include "minishell.h"

int	is_path_valid(t_data *data, char *path, int i, int j)
{
	char		temp[10000];
	struct stat	sb;
    int         len;

	len = ft_strlen(path);
	temp[0] = '\0';
	while (i < len)
	{
		while (path[i] == '/' && i < len)
			temp[j++] = path[i++];
		while (path[i] != '/' && i < len)
			temp[j++] = path[i++];
		temp[j] = '\0';
		if (stat(temp, &sb) < 0)
		{
			if (errno == ENOENT)
				error_msg_exit(0, data, path);
			else
				free_all_exit("Stat function failed!\n", 1, data, 0);
		}
		if (!S_ISDIR(sb.st_mode) && i < len)
		{
            ft_putstr_fd(path, 2);
            free_all_exit(": Not a directory\n", 1, data, 0);
		}
	}
	return (0);
}
