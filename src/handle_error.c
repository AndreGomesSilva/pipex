/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:24:47 by angomes-          #+#    #+#             */
/*   Updated: 2023/10/11 18:07:26 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	free_pipex(t_pipex *pipex)
{
	if (pipex->infile_fd)
		close(pipex->infile_fd);
	if (pipex->pipe_fd[READ])
		close(pipex->pipe_fd[READ]);
	if (pipex->pipe_fd[WRITE])
		close(pipex->pipe_fd[WRITE]);
	if (pipex->cmd->bin_path || pipex->cmd->splipted_path)
		free_matrix((pipex->cmd->splipted_path));
	if (pipex->cmd->exec_first_cmd)
		free_matrix(pipex->cmd->exec_first_cmd);
	if (pipex->cmd->exec_second_cmd)
		free_matrix(pipex->cmd->exec_second_cmd);
}

void	handle_error(int errnum, t_pipex *pipex)
{
	if (errnum == EACCES)
		ft_printf("%s: %s: %s", pipex->terminal_path, strerror(errnum), pipex->infile_path);
	else
		ft_printf("%s: \n", strerror(errnum));
	free_pipex(pipex);
	exit(EXIT_FAIL);
}
