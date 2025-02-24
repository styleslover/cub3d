/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariel <mariel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:42:01 by damoncad          #+#    #+#             */
/*   Updated: 2025/02/24 22:34:14 by mariel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*resize_and_copy_buffer(char *buffer, char *line_part)
{
	char	*new_buffer;
	size_t	part_length;
	size_t	remaining_length;

	remaining_length = 0;
	part_length = ft_strlen(line_part);
	new_buffer = ft_calloc(ft_strlen(buffer) - part_length, sizeof(char));
	if (!new_buffer)
	{
		free(buffer);
		return (NULL);
	}
	while (buffer[part_length])
	{
		new_buffer[remaining_length] = buffer[part_length];
		part_length++;
		remaining_length++;
	}
	free(buffer);
	return (new_buffer);
}

char	*extract_line_part( char *buffer)
{
	char	*line_part;
	size_t	i;

	i = 0;
	line_part = ft_calloc(ft_str_newline(buffer), sizeof(char));
	if (!line_part)
		return (NULL);
	while (buffer[i] != '\n' && buffer[i])
	{
		line_part[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line_part[i] = buffer[i];
	return (line_part);
}

char	*resize_buffer(char *buffer)
{
	char	*new_buffer;
	size_t	i;

	i = 0;
	new_buffer = ft_calloc(ft_strlen(buffer) + BUFFER_SIZE, sizeof(char));
	if (!new_buffer)
		return (NULL);
	while (buffer[i])
	{
		new_buffer[i] = buffer[i];
		i++;
	}
	free(buffer);
	return (new_buffer);
}

char	*initialize_buffer(int fd)
{
	char	*buffer;
	int		bytes_read;

	buffer = ft_calloc(BUFFER_SIZE, sizeof(char));
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (!buffer || bytes_read <= 0)
	{
		if (bytes_read <= 0)
			free(buffer);
		return (NULL);
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line_part;
	size_t		current_position;
	int			buffer_length;

	current_position = 0;
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (!buffer)
	{
		buffer = initialize_buffer(fd);
		if (!buffer)
			return (NULL);
	}
	buffer_length = ft_strlen(buffer);
	while (ft_nl(buffer) == 0 && buffer_length > 0)
	{
		buffer = resize_buffer(buffer);
		current_position += buffer_length;
		buffer_length = read(fd, &buffer[current_position], BUFFER_SIZE);
	}
	line_part = extract_line_part(buffer);
	buffer = resize_and_copy_buffer(buffer, line_part);
	return (line_part);
}

//#include <stdio.h>
//#include <fcntl.h>
//#include "get_next_line.h"
//
//int main()
//{
//	char	*line;
//	int		fd;
//
//	fd = open("example.txt", O_RDONLY);
//	if (fd == -1)
//	{
//		printf("Failed to open the file.\n");
//		return (1);
//	}
//
//	while ((line = get_next_line(fd)) != NULL)
//	{
//		printf("%s\n", line);
//		free(line);
//	}
//	//printf("%s", get_next_line(fd));
//	close(fd);
//	return (0);
//}
