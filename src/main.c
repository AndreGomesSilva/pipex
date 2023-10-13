/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:24:03 by angomes-          #+#    #+#             */
/*   Updated: 2023/10/13 18:35:52 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static void	set_pipex(char **argv, char **envp, t_pipex *pipex)
{
	pipex->infile_path = argv[1];
	pipex->outfile_path = argv[4];
	pipex->cmd->path = get_path(envp);
	pipex->cmd->first_cmd = argv[2];
	pipex->cmd->second_cmd = argv[3];
	pipex->terminal_path = get_terminal(envp);
	get_cmd(pipex);
}

static int	pipex_init(t_pipex *pipex, char **envp)
{
	if (pipe(pipex->pipe_fd) == ERROR)
		handle_error(errno, pipex);
	pipex->pid = fork();
	if (pipex->pid == ERROR)
		handle_error(errno, pipex);
	else if (pipex->pid == 0)
		child_process(pipex, envp);
	else if (pipex->pid > 0)
		parent_process(pipex, envp);
	if (wait(NULL) == ERROR)
		handle_error(errno, pipex);
	return (EXIT_OK);
}

int	main(int argc, char **argv, char *envp[])
{
	t_pipex	pipex;
	t_cmd	cmd;

	ft_bzero(&pipex, sizeof(t_pipex));
	ft_bzero(&cmd, sizeof(t_cmd));
	pipex.cmd = &cmd;
	if (argc == 5)
	{
		set_pipex(argv, envp, &pipex);
		if (!check_args(argv, &pipex) && pipex.cmd->path)
			pipex_init(&pipex, envp);
		else
		{
			ft_printf("%s: invalid args\n", pipex.terminal_path);
			exit(EXIT_FAIL);
		}
	}
	else
	{
		ft_printf("%s :invalid number argument\n", pipex.terminal_path);
		return (EXIT_FAIL);
	}
	free_pipex(&pipex);
	return (EXIT_OK);
}
