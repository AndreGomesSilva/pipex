#include "../inc/pipex.h"

void child_process(t_pipex *pipex)
{
	ft_printf("Child: child pid %d: \n", pipex->pid);
	if (close(pipex->pipe_fd[READ]) != 0)
		handle_error(errno, pipex);
	pipex->infile_fd = open(pipex->infile_path, O_RDONLY);
	if (pipex->infile_fd == ERROR)
		handle_error(errno, pipex);
//	dup2(pipex->pipe_fd[WRITE], STDOUT_FILENO);
	while(read(pipex->infile_fd, &pipex->buf, 1))
	{
		if (write(pipex->pipe_fd[WRITE], &pipex->buf, sizeof(char)) == ERROR)
			handle_error(errno, pipex);
	}
	close(pipex->pipe_fd[WRITE]);
	close(pipex->infile_fd);
	ft_printf("finish child process\n");
}

void parent_process(t_pipex *pipex)
{
	int status;
	waitpid(pipex->pid, &status, 0 );
	ft_printf("parent pid %d: \n", pipex->pid);

	close(pipex->pipe_fd[WRITE]);
//	dup2(pipex->pipe_fd[READ], STDIN_FILENO);
	while (read(pipex->pipe_fd[READ], &pipex->buf, sizeof(char)))
	{
		write(1, &pipex->buf, sizeof(char));
	}
	close(pipex->pipe_fd[READ]);
	ft_printf("\nfinish the parent process\n")	;
}