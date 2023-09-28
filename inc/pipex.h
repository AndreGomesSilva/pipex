//
// Created by angomes- on 9/22/23.
//

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libraries/libft/inc/libft.h"

typedef struct s_pipex
{
	char *infile;
	char *outfile;
	char *cmd1;
	char *cmd2;
	int pid;
} t_pipex;

void	pipex(int fd);

#endif
