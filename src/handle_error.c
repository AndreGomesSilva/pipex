#include "../inc/pipex.h"

void free_pipex(t_pipex *pipex)
{
	if (pipex->infile_fd)
		close(pipex->infile_fd);
	if (pipex->pipe_fd[READ])
		close(pipex->pipe_fd[READ]);
	if (pipex->pipe_fd[WRITE])
		close(pipex->pipe_fd[WRITE]);
	if (pipex->cmd1)
		free(pipex->cmd1);
	if (pipex->cmd2)
		free(pipex->cmd2);
}

void handle_error(int errnum, t_pipex *pipex)
{
	ft_printf("Error: %s\n", strerror(errnum));
	free_pipex(pipex);
	exit(EXIT_FAIL);
}