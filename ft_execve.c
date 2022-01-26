/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 16:47:26 by rasaboun          #+#    #+#             */
/*   Updated: 2021/08/06 16:47:26 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	void	checkexec(char **path, char **envp, char **argv)
{
	int		i;
	char	*rpath;
	char	*tmp;

	rpath = NULL;
	tmp = NULL;
	i = 0;
	while (path[i] != NULL)
	{
		tmp = ft_strjoin(path[i], "/");
		rpath = ft_strjoin(tmp, argv[0]);
		free(tmp);
		if (access(rpath, X_OK) == 0)
		{
			execve(rpath, argv, envp);
			perror("Error execve");
			freeall(path);
			free(argv);
			free(rpath);
			exit(0);
		}
		free(rpath);
		i++;
	}
	freeall(path);
}

void	ft_execv(char **path, char **envp, char **argv)
{
	checkexec(path, envp, argv);
	if (access(argv[0], X_OK) == 0)
	{
		execve(argv[0], argv, envp);
		perror("Error execve");
		freeall(argv);
		exit(0);
	}
	else
	{
		write(2, "command not found", 18);
		freeall(argv);
		exit(0);
	}
}
