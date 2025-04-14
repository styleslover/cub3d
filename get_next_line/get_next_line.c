/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:57:42 by mabrigo           #+#    #+#             */
/*   Updated: 2025/04/14 12:59:24 by damoncad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "get_next_line_utils.c"
/*
1) fd = open("nomefile.txt", O_<quello che vuoi fare>)
		O_RDONLY to read
		O_WRONLY to write
		O_RDWR to open and read
		------------------------
	https://pubs.opengroup.org/onlinepubs/007904875/functions/open.html
2) read a line in a file and return it as a string (til '\n') -> strdup
		if there's nothing to read -> NULL
3) read(fd, buf, bytes)
		buffer = where chars read are being stocked
		bytes = static variable, numbers of chard to be read
4) read function
		return Number of bytes read on success
		return 0 on reaching the end of file
		return -1 on error/signal interrupt
5) [bonus] massimo valore di fd = 1024
		0 input
		1 output
		3 error
		...
*/
#include "get_next_line.h"

char	*free_null(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*nl_strcat(char *str1, char *str2)
{
	char	*out;
	int		i;
	int		j;

	i = 0;
	out = nl_calloc(sizeof(char), nl_strlen(str1) + nl_strlen(str2) + 1);
	if (str1)
	{
		while (str1[i])
		{
			out[i] = str1[i];
			i++;
		}
	}
	j = 0;
	while (str2[j])
	{
		out[i] = str2[j];
		i++;
		j++;
	}
	out[i] = '\0';
	return (out);
}

char	*get_string(char **str, int fd)
{
	char	*buf;
	char	*temp;
	int		char_read;

	buf = nl_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (buf[check_nl(buf)] == '\0')
	{
		char_read = read(fd, buf, BUFFER_SIZE);
		if (char_read <= 0)
			break ;
		buf[char_read] = '\0';
		temp = nl_strcat(*str, buf);
		if (!temp)
			return (NULL);
		free(*str);
		*str = temp;
	}
	free(buf);
	if (char_read <= 0 && *str != NULL && nl_strlen(*str) == 0)
		return (free_null(str));
	return (*str);
}

char	*get_next_line(int fd)
{
	char		**str_ptr;
	char		*new_line;
	int			idx_newline;
	int			i;

	str_ptr = get_gnl_static();
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	*str_ptr = get_string(str_ptr, fd);
	if (*str_ptr == NULL)
		return (free_null(str_ptr));
	idx_newline = check_nl(*str_ptr);
	new_line = nl_calloc(sizeof(char), idx_newline + 2);
	if (!new_line)
		return (NULL);
	i = -1;
	while (++i <= idx_newline)
		new_line[i] = (*str_ptr)[i];
	nl_bzero(str_ptr, idx_newline);
	if (!*new_line)
		free_null(str_ptr);
	return (new_line);
}

void	clear_gnl(void)
{
	char	**str_ptr;

	str_ptr = get_gnl_static();
	if (*str_ptr)
	{
		free(*str_ptr);
		*str_ptr = NULL;
	}
}

/*int	main()
{
	char	*stringa;
	int		fd;

	fd = open("fd7.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Errore nell'apertura del file");
		return (1);
	}
	stringa = get_next_line(fd);
	int i = 0;
	printf("[%d]%s\n",i++, stringa);
	while (stringa)
	{
		free(stringa);
		stringa = get_next_line(fd);
		printf("[%d]%s\n",i++, stringa);
	}
}*/
