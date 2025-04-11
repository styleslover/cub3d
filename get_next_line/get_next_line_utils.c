/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:57:46 by mabrigo           #+#    #+#             */
/*   Updated: 2025/02/18 21:07:58 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_nl(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '\n')
			return (i);
	return (i);
}

int	nl_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*nl_bzero(char **s, int n)
{
	int		i;
	int		j;
	char	*p;
	int		len;

	len = nl_strlen(*s) - n;
	p = nl_calloc(sizeof(char), len + 1);
	if (!p)
		return (NULL);
	i = n + 1;
	j = 0;
	while (j < len)
		p[j++] = (*s)[i++];
	free(*s);
	*s = p;
	return (p);
}

void	*nl_calloc(int nmemb, int size)
{
	char	*ptr;
	int		i;

	ptr = malloc(nmemb * size);
	i = -1;
	if (ptr == NULL)
		return (ptr);
	else
	{
		while (++i < nmemb * size)
			ptr[i] = 0;
		return (ptr);
	}
}
