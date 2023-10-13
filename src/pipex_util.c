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
