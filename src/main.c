#include "../inc/pipex.h"

static void set_pipex(char **argv, char **envp, t_pipex *pipex)
{
	pipex->infile_path = argv[1];
	pipex->outfile_path = argv[4];
	pipex->bin_path = get_bin_path(envp);
	pipex->cmd1 = argv[2];
	pipex->cmd2 = argv[3];
	pipex->bin_path = join_cmd_path(pipex->bin_path, pipex->cmd1);
	create_argv_to_execve(pipex, pipex->cmd1);
}

static int pipex_init(t_pipex *pipex)
{

	if (pipe(pipex->pipe_fd) == ERROR)
		handle_error(errno, pipex);
	pipex->pid = fork();
	if (pipex->pid == ERROR)
		handle_error(errno, pipex);
	else if(pipex->pid == 0)
		child_process(pipex);
	else if(pipex->pid > 0)
		parent_process(pipex);
	return (EXIT_OK);
}

#include <stdio.h>
int	main(int argc, char **argv, char *envp[])
{
	t_pipex pipex;
	ft_bzero(&pipex, sizeof(t_pipex));
//	int i;
//
//	i = 0;
//
//	while(envp[i])
//	{
//		ft_printf("%s\n", envp[i]);
//		i++;
//	}
	if (argc == 5)
	{
		set_pipex(argv, envp, &pipex);
		if (!check_args(argv, &pipex) && pipex.bin_path) {
			if (execve("/usr/bin/ls",pipex.exec_argv , envp) == ERROR)
				handle_error(errno, &pipex);
			pipex_init(&pipex);
		}
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