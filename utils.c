/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:31:10 by mabrigo           #+#    #+#             */
/*   Updated: 2025/04/23 16:04:22 by damoncad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	my_strchr(char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return (1);
		s++;
	}
	return (0);
}

char	*trim_end_spaces(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = ft_strlen(s) - 1;
	while (i >= 0 && ft_strchr(" \t\v\r\n", s[i]))
		i--;
	s[i + 1] = '\0';
	return (s);
}

char	*strcmp_from_i(int i, char *src)
{
	if (!src || !src[i])
		return (NULL);
	return (ft_strtrim(src + i, " \t\r\n"));
}

int	count_lines(char *av, int fd)
{
	int		lines;
	char	*line;

	lines = 0;
	fd = open(av, O_RDONLY);
	if (fd < 0)
		return (0);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		lines++;
		free(line);
	}
	close(fd);
	return (lines);
}

char	*trim_newline(char *line)
{
	int	len;

	len = strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}
