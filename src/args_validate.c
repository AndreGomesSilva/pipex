//
// Created by angomes on 01/10/23.
//

#include "../inc/pipex.h"

int check_program_name(char **str)
{
	char *right_name;
	char *pass_name;

	pass_name = *(str + 0);
	right_name = "/pipex";
	while(pass_name && *(pass_name + 6))
		pass_name++;
	if (!ft_strncmp(right_name, pass_name, 6))
		return (EXIT_OK);
	return (EXIT_FAIL);
}


int check_infile(char *infile)
{
	if(access(infile, F_OK) != 0)
		handle_error(errno);
	return (EXIT_OK);
}

int check_args(int number_args, char **args)
{
	if (number_args == 5 && !check_program_name(args) && !check_infile(args[1]))
		return (EXIT_OK);
	return (EXIT_FAIL);
}
