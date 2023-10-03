#include "../inc/pipex.h"

void child_process(t_pipex *pipex)
{
	ft_printf("Child: child pid %d: \n", pipex->pid);
	close(pipex->pipe_fd[READ]);
	pipex->infile_fd = open(pipex->infile_path, O_RDONLY | O_TRUNC | O_CREAT, 0644);
	if (pipex->infile_fd == ERROR)
		handle_error(errno, pipex);
	int a;
	a = 4;
	if (write(pipex->pipe_fd[WRITE], &a, sizeof(int)) == ERROR)
		handle_error(errno, pipex);
	ft_printf("Child: we are in the child process\n");
	close(pipex->pipe_fd[WRITE]);
	close(pipex->infile_fd);
	exit(20);
}

void parent_process(t_pipex *pipex)
{
	int status;
	waitpid(pipex->pid, &status, 0 );
	ft_printf("parent pid %d: \n", pipex->pid);
	ft_printf("Parent: my child exited with status %d\n", status);
	if (WIFEXITED(status))
	{
		ft_printf("Parent : My child's exit code is %d\n", WEXITSTATUS(status));
		if (WEXITSTATUS(status) == 20)
			ft_printf("Parent: That's the code I expected!\n");
		else
			ft_printf("Parent: I was not expecting that\n");
	}
	close(pipex->pipe_fd[WRITE]);
	int *b;
	if (read(pipex->pipe_fd[READ], &b, sizeof(int)) == ERROR)
		handle_error(errno, pipex);
	ft_printf("we are in the parent process\n");
	ft_printf("my message from children %d \n", b);
	close(pipex->pipe_fd[READ]);
}