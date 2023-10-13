/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:24:53 by angomes-          #+#    #+#             */
/*   Updated: 2023/10/13 18:38:04 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	get_cmd(t_pipex *pipex)
{
	pipex->cmd->exec_first_cmd = split_argv_cmd(pipex->cmd->first_cmd);
	pipex->cmd->exec_second_cmd = split_argv_cmd(pipex->cmd->second_cmd);
	pipex->cmd->split_path_child = split_path(pipex->cmd->path,
			pipex->cmd->exec_first_cmd[0]);
	pipex->cmd->split_path_parent = split_path(pipex->cmd->path,
			pipex->cmd->exec_second_cmd[0]);
	if (!pipex->cmd->split_path_parent || !pipex->cmd->split_path_child)
	{
		ft_printf("%s: command not found: \n", pipex->terminal_path);
		free_pipex(pipex);
		exit(EXIT_FAIL);
	}
	pipex->cmd->bin_path_child = get_bin_path(pipex->cmd->split_path_child);
	pipex->cmd->bin_path_parent = get_bin_path(pipex->cmd->split_path_parent);
	if (!pipex->cmd->bin_path_parent || !pipex->cmd->bin_path_child)
	{
		if (!pipex->cmd->bin_path_child)
			ft_printf("%s: command not found: %s\n", pipex->terminal_path,
				pipex->cmd->first_cmd);
		else
			ft_printf("%s: command not found: %s\n", pipex->terminal_path,
				pipex->cmd->second_cmd);
		free_pipex(pipex);
		exit(EXIT_FAIL);
	}
}

char	**split_argv_cmd(char *cmd)
{
	char	**split_cmd;

	if (!cmd)
		return (NULL);
	split_cmd = ft_split(cmd, ' ');
	return (split_cmd);
}

char	*get_bin_path(char **split_path)
{
	int	i;

	i = 0;
	while (split_path[i])
	{
		if (!access(split_path[i], X_OK))
			return (split_path[i]);
		i++;
	}
	return (NULL);
}

char	**split_path(char *str, char *cmd)
{
	char	**bin;
	int		i;

	i = 0;
	if (!cmd || !str)
		return (NULL);
	bin = ft_split(str, ':');
	while (bin[i])
	{
		bin[i] = ft_join_path(bin[i], "/");
		bin[i] = ft_join_path(bin[i], cmd);
		i++;
	}
	return (bin);
}

char	*get_path(char **str)
{
	int		i;
	char	*path;

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
