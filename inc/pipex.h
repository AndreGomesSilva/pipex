/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:27:51 by angomes-          #+#    #+#             */
/*   Updated: 2023/10/13 18:37:41 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define EXIT_OK 0
# define EXIT_FAIL 1
# define WRITE 1
# define READ 0
# define ERROR (-1)

# include "../libraries/libft/inc/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_cmd
{
	char	*path;
	char	**split_path;
	char	*bin_path;
	char	*first_cmd;
	char	*second_cmd;
	char	**exec_cmd;
	char	*new_cmd;
}			t_cmd;

typedef struct s_pipex
{
	int		infile_fd;
	int		outfile_fd;
	char	*infile_path;
	char	*outfile_path;
	char	*terminal_path;
	pid_t	pid;
	int		pipe_fd[2];
	t_cmd	*cmd;
}			t_pipex;

int			check_infile(t_pipex *pipex);
void		remove_quotation_mark(t_pipex *pipex, char *cmd);
void		get_cmd(t_pipex *pipex, char *cmd);
char		*get_terminal(char **str);
char		*ft_join_path(char *s1, char *s2);
char		*get_bin_path(char **split_path);
char		**split_path(char *str, char *cmd);
void		free_matrix(char **matrix);
char		**split_argv_cmd(char *cmd);
char		*get_path(char **str);
void		handle_error(int errnum, t_pipex *pipex, int flag);
int			check_args(char **args);
void		free_pipex(t_pipex *pipex);
void		child_process(t_pipex *pipex, char **envp);
void		parent_process(t_pipex *pipex, char **envp);
#endif
