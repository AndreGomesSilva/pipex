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
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include "../libraries/libft/inc/libft.h"


typedef struct s_pipex
{
	int infile_fd;
	char **bin_path;
	int outfile_fd;
	char *infile_path;
	char *outfile_path;
	char *cmd1;
	char *cmd2;
	char buf;
	char **exec_argv;
	pid_t pid;
	int pipe_fd[2];
} t_pipex;


char **join_cmd_path(char *str, char *cmd);
void free_matrix(char **matrix);
void create_argv_to_execve(t_pipex *pipex, char *cmd);
char* get_bin_path(char **str);
void handle_error(int errnum, t_pipex *pipex);
int check_args(char **args, t_pipex *pipex);
void free_pipex(t_pipex *pipex);
void child_process(t_pipex *pipex);
void parent_process(t_pipex *pipex);
#endif
