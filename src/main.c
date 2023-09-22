//
// Created by angomes- on 9/22/23.
//

#include "../inc/pipex.h"
#include <stdio.h>
void	pipex(int fd) {

	if (access("input.txt", R_OK) != -1)
		ft_printf("I have permission \n");
	else
		ft_printf("I don't have permission \n");

	pid_t pid;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
		ft_printf("This is the child process. (pid: %d) \n", getpid());
	else
		ft_printf("This is the parent process.  (pid: %d) \n ", getpid());
	dup2 (fd, STDOUT_FILENO);
	ft_printf("add this to the file");

}

int	main(void)
{
	int fd;

	fd = open("input.txt", O_WRONLY | O_CREAT, 0644);

	pipex(fd);
	close(fd);
	return (0);
}