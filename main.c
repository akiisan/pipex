/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 16:47:11 by rasaboun          #+#    #+#             */
/*   Updated: 2021/08/06 16:54:01 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	freeall(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static	void	processone(t_pipex *p)
{
	p->child = fork();
	if (p->child < 0)
	{
		perror("failed fork");
	}
	if (p->child == 0)
	{
		p->in = open(p->argv[1], O_RDONLY);
		if (p->in <= 1)
			perror("no such file");
		close(p->fd[0]);
		dup2(p->in, STDIN_FILENO);
		dup2(p->fd[1], STDOUT_FILENO);
		close(p->fd[1]);
		p->cmdd = ft_split(p->argv[2], ' ');
		ft_execv(p->path, p->envp, p->cmdd);
	}
}

static	void	processtwo(t_pipex *p)
{
	p->child2 = fork();
	if (p->child2 < 0)
	{
		perror("failed fork");
	}
	if (p->child2 == 0)
	{
		p->out = open(p->argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (p->out <= 1)
			perror("ERROR Create file");
		close(p->fd[1]);
		dup2(p->fd[0], 0);
		dup2(p->out, 1);
		close(p->fd[0]);
		p->cmd = ft_split(p->argv[3], ' ');
		ft_execv(p->path, p->envp, p->cmd);
	}
}

static	void	initpipex(t_pipex *pipex, char **argv, char **envp)
{
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->child2 = 0;
	pipex->child = 0;
	pipex->cmd = NULL;
	pipex->cmdd = NULL;
	pipex->in = 0;
	pipex->out = 0;
	pipex->path = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	initpipex(&pipex, argv, envp);
	checkerror(argc, &pipex, envp);
	processone(&pipex);
	processtwo(&pipex);
	close(pipex.fd[0]);
	close(pipex.fd[1]);
	waitpid(pipex.child, NULL, 0);
	waitpid(pipex.child2, NULL, 0);
	freeall(pipex.path);
	return (0);
}
