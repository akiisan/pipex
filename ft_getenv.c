/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 16:55:40 by rasaboun          #+#    #+#             */
/*   Updated: 2021/08/06 16:55:41 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_getenv(char **env)
{
	int		i;
	int		m;
	char	*allpath;
	char	**spath;

	allpath = NULL;
	m = 0;
	i = 0;
	spath = NULL;
	while (env[i] != NULL && ft_strncmp("PATH", env[i], 4) != 0)
		i++;
	if (ft_strncmp("PATH", env[i], 4) == 0)
	{
		m = ft_strlen(env[i]);
		allpath = ft_substr(env[i], 5, m);
		spath = ft_split(allpath, ':');
		free(allpath);
		return (spath);
	}
	return (NULL);
}
