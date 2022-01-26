/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 16:47:29 by rasaboun          #+#    #+#             */
/*   Updated: 2021/08/06 16:54:54 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	void	ft_bzero(void *s, size_t n)
{
	int				i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while ((size_t)i < n)
	{
		str[i] = '\0';
		i++;
	}
}

static void	*malzero(size_t size)
{
	void	*temp;

	temp = malloc(size);
	if (!temp)
		return (NULL);
	ft_bzero(temp, size);
	return (temp);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*tab;

	tab = (void *)malzero(size * count);
	if (!tab)
		return (NULL);
	return (tab);
}
