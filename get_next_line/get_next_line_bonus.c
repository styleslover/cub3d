/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:13:34 by damoncad          #+#    #+#             */
/*   Updated: 2024/03/13 12:16:42 by damoncad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*resize_and_copy_buffer(char *buffer, char *line_part)
{
	char	*new_buffer;
	size_t	part_length;
	size_t	remaining_length;

	part_length = ft_strlen(line_part);
	remaining_length = 0;
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
	while ((buffer[i] != '\n') && buffer[i])
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

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= MAX_FD)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
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
	static char	*buffer[MAX_FD];
	char		*line_part;
	size_t		current_position;
	int			buffer_length;

	current_position = 0;
	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= MAX_FD)
		return (NULL);
	if (!buffer[fd])
	{
		buffer[fd] = initialize_buffer(fd);
		if (!buffer[fd])
			return (NULL);
	}
	buffer_length = ft_strlen(buffer[fd]);
	while (ft_nl(buffer[fd]) == 0 && buffer_length > 0)
	{
		buffer[fd] = resize_buffer(buffer[fd]);
		current_position += buffer_length;
		buffer_length = read(fd, &buffer[fd][current_position], BUFFER_SIZE);
	}
	line_part = extract_line_part(buffer[fd]);
	buffer[fd] = resize_and_copy_buffer(buffer[fd], line_part);
	return (line_part);
}

/*int	main(void)
{
	char	*line;
	int		a;
	int		fd;
	int		fd2;
	int		fd3;

	fd = open("example.txt", O_RDONLY);
	fd2 = open("example2.txt", O_RDONLY);
	fd3 = open("example3.txt", O_RDONLY);

	a = 1;
	while ((a < 7))
	{
		line = get_next_line(fd);
		printf("line [%02d]: %s\n", a, line);
		free(line);
		line = get_next_line(fd2);
		printf("line fd2[%02d]: %s\n", a, line);
		free(line);
		line = get_next_line(fd3);
		printf("line fd3[%02d]: %s\n", a, line);
		free(line);
		a++;
	}
	close(fd);
	close(fd2);
	close(fd3);
	//printf("%s", get_next_line(fd));
	return (0);
}*/