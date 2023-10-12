/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:24:37 by angomes-          #+#    #+#             */
/*   Updated: 2023/10/11 18:20:57 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	get_cmd(t_pipex *pipex)
{
	if (pipex->pid == 0)
	{
		pipex->cmd->exec_first_cmd = split_argv_cmd(pipex->cmd->first_cmd);
		pipex->cmd->splipted_path = split_path(pipex->cmd->path,
				pipex->cmd->exec_first_cmd[0]);
	}
	else if (pipex->pid > 0)
	{
		pipex->cmd->exec_second_cmd = split_argv_cmd(pipex->cmd->second_cmd);
		pipex->cmd->splipted_path = split_path(pipex->cmd->path,
				pipex->cmd->exec_second_cmd[0]);
	}
	if ((!pipex->cmd->exec_second_cmd || !pipex->cmd->exec_first_cmd)
		&& !pipex->cmd->splipted_path)
	{
		ft_printf("Error:\n Problem to execute the commands\n");
		free_pipex(pipex);
		exit(EXIT_FAIL);
	}
	pipex->cmd->bin_path = get_bin_path(pipex->cmd->splipted_path);
}

void	child_process(t_pipex *pipex, char **envp)
{
	if (close(pipex->pipe_fd[READ]) == ERROR)
		handle_error(errno, pipex);
	get_cmd(pipex);
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
	if (execve(pipex->cmd->bin_path, pipex->cmd->exec_first_cmd, envp) == ERROR)
		handle_error(errno, pipex);
}

void	parent_process(t_pipex *pipex, char **envp)
{
	if (close(pipex->pipe_fd[WRITE]) == ERROR)
		handle_error(errno, pipex);
	get_cmd(pipex);
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
	if (execve(pipex->cmd->bin_path, pipex->cmd->exec_second_cmd,
			envp) == ERROR)
		handle_error(errno, pipex);
}
