#include "../inc/pipex.h"

void child_process(t_pipex *pipex)
{
	close(pipex->pipe_fd[READ]);
	pipex->infile_fd = open(pipex->infile_path, O_RDONLY);
	if (pipex->infile_fd == ERROR)
		handle_error(errno, pipex);
	int a;
	a = 4;
	if (write(pipex->pipe_fd[WRITE], &a, sizeof(int)) == ERROR)
		handle_error(errno, pipex);
	ft_printf("we are in the child process\n");
	close(pipex->pipe_fd[WRITE]);
	close(pipex->infile_fd);
}

void parent_process(t_pipex *pipex)
{
	close(pipex->pipe_fd[WRITE]);
	int *b;
	if (read(pipex->pipe_fd[READ], &b, sizeof(int)) == ERROR)
		handle_error(errno, pipex);
	ft_printf("we are in the parent process\n");
	ft_printf("my message from children %d \n", b);
	close(pipex->pipe_fd[READ]);
}