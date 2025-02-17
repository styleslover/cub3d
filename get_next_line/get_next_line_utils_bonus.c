/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils _bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:54:07 by damoncad          #+#    #+#             */
/*   Updated: 2024/02/13 22:47:40 by damoncad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_nl(char *buffer)
{
	size_t	p;

	p = 0;
	while (buffer[p])
	{
		if (buffer[p] == '\n')
			return (1);
		p++;
	}
	return (0);
}

size_t	ft_str_newline( char *buffer)
{
	size_t	p;

	p = 0;
	while (buffer[p] != '\n' && buffer[p])
		p++;
	if (buffer[p] == '\n')
		p++;
	return (p);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*buffer;
	size_t	p;
	size_t	i;

	p = 0;
	i = nmemb * size;
	if (nmemb == 0 || size == 0)
		return (NULL);
	buffer = malloc(i + 1);
	if (!buffer)
		return (NULL);
	while (p <= i)
	{
		buffer[p] = '\0';
		p++;
	}
	return (buffer);
}

int	ft_strlen(char *buffer)
{
	size_t	a;

	a = 0;
	while (buffer[a])
		a++;
	return (a);
}
