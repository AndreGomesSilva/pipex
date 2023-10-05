//
// Created by angomes- on 10/4/23.
//

#include "../inc/pipex.h"

char *get_bin_path(char **str)
{
	int i;
	char *path;

	i = 0;
	while (str[i])
	{
		if (!ft_strncmp(str[i], "PATH=", 5))
		{
			path = str[i];
			while (*path != '=')
				path++;
			return (++path);
		}
		i++;
	}
	return (NULL);
}