//
// Created by angomes- on 9/22/23.
//

#ifndef PIPEX_H
# define PIPEX_H
# define EXIT_OK 0
# define EXIT_FAIL 1
# define WRITE 1
# define READ 0
# define ERROR (-1)

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libraries/libft/inc/libft.h"

typedef struct s_pipex
{
	int infile_fd;
	int outfile_fd;
	char *infile_path;
	char *outfile_path;
	char *cmd1;
	char *cmd2;
	int pid;
	int pipe_fd[2];
} t_pipex;

void handle_error(int errnum, t_pipex *pipex);
int check_args(int number_args, char **args);
void child_process(t_pipex *pipex);
void parent_process(t_pipex *pipex);
#endif
