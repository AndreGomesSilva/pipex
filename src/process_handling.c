/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:24:37 by angomes-          #+#    #+#             */
/*   Updated: 2023/10/13 18:36:35 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char	*get_terminal(char **str)
{
	int		i;
	int		len;
	char	*path;

	i = 0;
	while (str[i])
	{
		if (!ft_strncmp(str[i], "SHELL", 5))
		{
			len = (int)ft_strlen(str[i]);
			path = str[i];
			while (len)
			{
				if (path[len] == '/')
					return (&path[len + 1]);
				len--;
			}
		}
		i++;
	}
	return (NULL);
}

void	child_process(t_pipex *pipex, char **envp)
{
	if (close(pipex->pipe_fd[READ]) == ERROR)
		handle_error(errno, pipex);
	pipex->infile_fd = open(pipex->infile_path, O_RDONLY);
	if (pipex->infile_fd == ERROR)
		handle_error(errno, pipex);
	if (dup2(pipex->infile_fd, STDIN_FILENO) == ERROR)
		handle_error(errno, pipex);
	if (dup2(pipex->pipe_fd[WRITE], STDOUT_FILENO) == ERROR)
		handle_error(errno, pipex);
	if (close(pipex->infile_fd) == ERROR)
		handle_error(errno, pipex);
	if (close(pipex->pipe_fd[WRITE]) == ERROR)
		handle_error(errno, pipex);
	if (execve(pipex->cmd->bin_path_child, pipex->cmd->exec_first_cmd,
			envp) == ERROR)
		handle_error(errno, pipex);
}

void	parent_process(t_pipex *pipex, char **envp)
{
	if (close(pipex->pipe_fd[WRITE]) == ERROR)
		handle_error(errno, pipex);
	pipex->outfile_fd = open(pipex->outfile_path, O_WRONLY | O_CREAT | O_TRUNC,
			0644);
	if (pipex->outfile_fd == ERROR)
		handle_error(errno, pipex);
	if (dup2(pipex->outfile_fd, STDOUT_FILENO) == ERROR)
		handle_error(errno, pipex);
	if (dup2(pipex->pipe_fd[READ], STDIN_FILENO) == ERROR)
		handle_error(errno, pipex);
	if (close(pipex->pipe_fd[READ]) == ERROR)
		handle_error(errno, pipex);
	if (execve(pipex->cmd->bin_path_parent, pipex->cmd->exec_second_cmd,
			envp) == ERROR)
		handle_error(errno, pipex);
}
