//
// Created by angomes- on 10/4/23.
//

#include "../inc/pipex.h"

char	*ft_join_path(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*new_str;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_str = (char *) malloc((s1_len + s2_len + 1) * sizeof(char));
	if (new_str != NULL)
	{
		ft_strlcpy(new_str, s1, s1_len + 1);
		ft_strlcat(new_str, s2, s1_len + s2_len + 1);
		free(s1);
		return (new_str);
	}
	return (NULL);
}
void create_argv_to_execve(t_pipex *pipex, char *cmd)
{
	pipex->exec_argv = ft_split(cmd, ' ');
}

char **join_cmd_path(char *str, char *cmd)
{
	char **bin;
	char *slash;
	int i;

	i = 0;
	slash = ft_calloc(2, sizeof(char));
	slash[0] = '/';
	bin = ft_split(str, ':');
	while (bin[i])
	{
		bin[i] = ft_join_path(bin[i], slash);
		bin[i] = ft_join_path(bin[i], cmd);
		i++;
	}
	free(slash);
	return (bin);
}

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