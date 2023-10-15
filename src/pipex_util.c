/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 18:36:00 by angomes-          #+#    #+#             */
/*   Updated: 2023/10/13 18:36:38 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static int	mark_strlen(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != 39)
			j++;
		i++;
	}
	return (j);
}

void	remove_quatation_mark(t_pipex *pipex, char *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	pipex->cmd->new_cmd = ft_calloc(mark_strlen(cmd) + 1, sizeof (char));
	while (cmd[i])
	{
		if (cmd[i] != 39)
		{
			pipex->cmd->new_cmd[j] = cmd[i];
			j++;
		}
		i++;
	}
}

char	*ft_join_path(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*new_str;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_str = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (new_str != NULL)
	{
		ft_strlcpy(new_str, s1, s1_len + 1);
		ft_strlcat(new_str, s2, s1_len + s2_len + 1);
		free(s1);
		return (new_str);
	}
	free(new_str);
	return (NULL);
}
