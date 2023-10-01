#include "../inc/pipex.h"

static int pipex_init(t_pipex *pipex, char **argv)
{
	pipex->infile_path = argv[1];
	pipex->outfile_path = argv[4];
	if (pipe(pipex->pipe_fd) == ERROR)
		handle_error(errno, pipex);
	pipex->pid = fork();
	if (pipex->pid == ERROR)
		handle_error(errno, pipex);
	if (pipex->pid == 0)
		child_process(pipex);
	else
	{
		wait(NULL);
		parent_process(pipex);
	}
	return (EXIT_OK);
}

int	main(int argc, char **argv)
{
	t_pipex pipex;
	ft_bzero(&pipex, sizeof(t_pipex));
	if (!check_args(argc, argv))
		pipex_init(&pipex, argv);
	else
	{
		ft_printf("invalid argument\n");
		return (EXIT_FAIL);
	}
	ft_printf("finish\n");
	return (EXIT_OK);
}