/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:31:10 by mabrigo           #+#    #+#             */
/*   Updated: 2025/04/01 19:40:03 by mabrigo          ###   ########.fr       */
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
	int		j;
	int		len;
	char	*dest;

	if (!src)
		return (NULL);
	len = ft_strlen(src) - i + 1;
	if (len <= 0)
		return (NULL);
	dest = malloc(sizeof(char) * len);
	if (!dest)
		return (NULL);
	j = 0;
	while (src[i])
		dest[j++] = src[i++];
	dest[j] = '\0';
	dest = ft_strtrim(dest, " ");
	dest = trim_end_spaces(dest);
	return (dest);
}

int	count_lines(char *av, int fd)
{
	int		lines;
	char	*line;

	lines = 0;
	fd = open(av, O_RDONLY);
	if (fd < 0)
		return (0);
	while ((line = get_next_line(fd)))
	{
		lines++;
		free(line);
	}
	close(fd);
	return (lines);
}

char *trim_newline(char *line)
{
	int len = strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return line;
}