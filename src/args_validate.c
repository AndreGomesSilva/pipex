/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_validate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:25:05 by angomes-          #+#    #+#             */
/*   Updated: 2023/10/11 18:07:16 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static int	check_program_name(char **str)
{
	char	*right_name;
	char	*pass_name;

	pass_name = *(str + 0);
	right_name = "/pipex";
	while (pass_name && *(pass_name + 6))
		pass_name++;
	if (!ft_strncmp(right_name, pass_name, 6))
		return (EXIT_OK);
	return (EXIT_FAIL);
}

static int	check_infile(t_pipex *pipex)
{
	if (access(pipex->infile_path, F_OK) == ERROR || access(pipex->infile_path,
			R_OK) == ERROR)
		handle_error(errno, pipex);
	return (EXIT_OK);
}

int	check_args(char **args, t_pipex *pipex)
{
	if (!check_program_name(args) && !check_infile(pipex))
		return (EXIT_OK);
	return (EXIT_FAIL);
}
