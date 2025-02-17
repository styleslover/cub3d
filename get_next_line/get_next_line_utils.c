/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:54:07 by damoncad          #+#    #+#             */
/*   Updated: 2024/03/13 11:58:13 by damoncad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_nl(char *buffer)
{
	size_t	a;

	a = 0;
	while (buffer[a])
	{
		if (buffer[a] == '\n')
			return (1);
		a++;
	}
	return (0);
}

size_t	ft_str_newline( char *buffer)
{
	size_t	a;

	a = 0;
	while (buffer[a] != '\n' && buffer[a])
		a++;
	if (buffer[a] == '\n')
		a++;
	return (a);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*buffer;
	size_t	a;
	size_t	i;

	a = 0;
	i = nmemb * size;
	if (nmemb == 0 || size == 0)
		return (NULL);
	buffer = malloc(i + 1);
	if (!buffer)
		return (NULL);
	while (a <= i)
	{
		buffer[a] = '\0';
		a++;
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
