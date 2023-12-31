/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_validate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:25:05 by angomes-          #+#    #+#             */
/*   Updated: 2023/10/13 18:35:39 by angomes-         ###   ########.fr       */
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

int	check_infile(t_pipex *pipex)
{
	if (access(pipex->infile_path, F_OK) == ERROR)
		handle_error(2, pipex, 1);
	if (access(pipex->infile_path, R_OK) == ERROR)
		handle_error(13, pipex, 2);
	return (EXIT_OK);
}

int	check_args(char **args)
{
	if (!check_program_name(args))
		return (EXIT_OK);
	return (EXIT_FAIL);
}
