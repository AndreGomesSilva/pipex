#include "../inc/pipex.h"

static void set_pipex(char **argv, t_pipex *pipex)
{
	pipex->infile_path = argv[1];
	pipex->outfile_path = argv[4];
	pipex->cmd1 = argv[2];
	pipex->cmd2 = argv[3];
}

static int pipex_init(t_pipex *pipex)
{

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
	if (argc == 5)
	{
		set_pipex(argv, &pipex);
		if (!check_args(argv, &pipex))
			pipex_init(&pipex);
		else
		{
			ft_printf("invalid args");
			exit(EXIT_FAIL);
		}
	}
	else
	{
		ft_printf("invalid number argument\n");
		return (EXIT_FAIL);
	}
	free_pipex(&pipex);
	ft_printf("finish\n");
	return (EXIT_OK);
}