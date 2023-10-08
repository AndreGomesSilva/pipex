#include "../inc/pipex.h"

void free_matrix(char **matrix)
{
	int i;
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void free_pipex(t_pipex *pipex)
{
	if (pipex->infile_fd)
		close(pipex->infile_fd);
	if (pipex->pipe_fd[READ])
		close(pipex->pipe_fd[READ]);
	if (pipex->pipe_fd[WRITE])
		close(pipex->pipe_fd[WRITE]);
	if (pipex->cmd->bin_path)
		free_matrix((pipex->cmd->splipted_path));
	if (pipex->cmd->exec_first_cmd)
		free_matrix(pipex->cmd->exec_first_cmd);
	if (pipex->cmd->exec_second_cmd)
		free_matrix(pipex->cmd->exec_second_cmd);
}

void handle_error(int errnum, t_pipex *pipex)
{
	ft_printf("Error: %s\n", strerror(errnum));
	free_pipex(pipex);
	exit(EXIT_FAIL);
}