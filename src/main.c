//
// Created by angomes- on 9/22/23.
//

#include "../inc/pipex.h"
#include <stdio.h>

int check_args(char **str)
{
	if(!ft_strncmp(*str, "./pipex", 10))
	{
		printf("first arg %s", *str);
	}

	return (1);
}

int	main(int argc, char **argv)
{
	t_pipex pipex;
	ft_bzero(&pipex, sizeof(t_pipex));
	if (argc == 5)
	{
		check_args(argv);
	}
	else
	{
		return (1);
	}
	printf("finish");
	return (0);
}
//int main()
//{
//	int fd[2];
//	int id;
//
//	if (pipe(fd) == -1)
//	{
//		printf("problem with pipe");
//		return (1);
//	}
//	id = fork();
//	if (id == 0)
//	{
//		close(fd[0]);
//		int x;
//		printf("digite um numero: ");
//		scanf("%d", &x);
//		write(fd[1], &x, sizeof(int));
//		close(fd[1]);
//	}else
//	{
//		close(fd[1]);
//		int y;
//		read(fd[0], &y, sizeof(int));
//		printf("This is the value get from child process %d ", y);
//		close(fd[0]);
//	}
//}
//void	pipex(int fd) {
//
//	if (access("input.txt", R_OK) != -1)
//		ft_printf("I have permission \n");
//	else
//		ft_printf("I don't have permission \n");
//
//	pid_t pid;
//	pid = fork();
//	if (pid == -1)
//	{
//		perror("fork");
//		exit(EXIT_FAILURE);
//	}
//
//	if (pid == 0)
//		ft_printf("This is the child process. (pid: %d) \n", getpid());
//	else
//		ft_printf("This is the parent process.  (pid: %d) \n ", getpid());
//	dup2 (fd, STDOUT_FILENO);
//	ft_printf("add this to the file");
//
//}
//
//int	main(void)
//{
//	int fd;
//
//	fd = open("input.txt", O_WRONLY | O_CREAT, 0644);
//
//	pipex(fd);
//	close(fd);
//	return (0);
//}