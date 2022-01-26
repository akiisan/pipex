/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 16:47:21 by rasaboun          #+#    #+#             */
/*   Updated: 2021/08/06 16:54:41 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_count(const char *s, char c)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	if (s[i] == '\0')
		return (n);
	if (s[0] != c)
		n++;
	while (s[i + 1] != '\0')
	{
		if (s[i] == c && s[i + 1] != c)
			n++;
		i++;
	}
	return (n);
}

static char	*ft_substrr(const char *s, int min, int max)
{
	int		i;
	char	*s2;

	s2 = malloc(sizeof(char *) * (max - min + 1));
	if (!s2)
		return (NULL);
	i = 0;
	while (min < max)
	{
		s2[i] = s[min];
		i++;
		min++;
	}
	s2[i] = '\0';
	return (s2);
}

static void	ft_free(int n, char **s)
{
	while (n >= 0)
	{
		free(s[n]);
		n--;
	}
}

static	void	ft_while(const char *s, char **s2, char c)
{
	int	i;
	int	n;
	int	min;

	i = 0;
	n = 0;
	min = 0;
	while (s[i] != '\0')
	{
		while (s[i] && s[i] == c)
			i++;
		min = i;
		while (s[i] && s[i] != c)
			i++;
		if (n < ft_count(s, c))
		{
			s2[n] = ft_substrr(s, min, i);
			if (s2[n] == NULL)
				ft_free(n, s2);
		}
		n++;
	}
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		min;
	char	**s2;
	int		n;

	if (!s)
		return (NULL);
	n = 0;
	s2 = malloc(sizeof(char *) * (ft_count(s, c) + 1));
	if (s2 == NULL)
		return (0);
	s2[ft_count(s, c)] = 0;
	i = 0;
	ft_while(s, s2, c);
	return (s2);
}
