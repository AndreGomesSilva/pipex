/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:24:47 by angomes-          #+#    #+#             */
/*   Updated: 2023/10/13 18:35:45 by angomes-         ###   ########.fr       */
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
	if (pipex->cmd->split_path)
		free_matrix((pipex->cmd->split_path));
	if (pipex->cmd->exec_cmd)
		free_matrix(pipex->cmd->exec_cmd);
}

void	handle_error(int errnum, t_pipex *pipex, int flag)
{
	if (errnum == 13 && flag == 2)
		ft_printf("%s: %s: %s\n", pipex->terminal_path, strerror(errnum),
			pipex->infile_path);
	if (errnum == 13 && flag == 3)
		ft_printf("%s: %s: %s\n", pipex->terminal_path, strerror(errnum),
			pipex->outfile_path);
	if (errnum == 2 && flag == 1)
		ft_printf("%s: %s: %s\n", pipex->terminal_path, strerror(errnum),
			pipex->infile_path);
	if (!errnum && flag == 4)
		ft_printf("%s: %s\n", pipex->terminal_path,
			"problem in the wait function");
	if (!errnum && flag == 5)
		ft_printf("%s: %s\n", pipex->terminal_path,
			"problem in the fork function");
	if (!flag)
		ft_printf("%s: %s\n", pipex->terminal_path, strerror(errnum));
	free_pipex(pipex);
	exit(EXIT_FAIL);
}
