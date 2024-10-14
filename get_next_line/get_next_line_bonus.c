/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 21:02:26 by mabrigo           #+#    #+#             */
/*   Updated: 2024/01/29 20:51:23 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	out = ft_calloc(sizeof(char), nl_strlen(str1) + nl_strlen(str2) + 1);
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

	buf = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
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
	static char	*str[1024];
	char		*new_line;
	int			idx_newline;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str[fd] = get_string(&str[fd], fd);
	if (str[fd] == NULL)
		return (free_null(&str[fd]));
	idx_newline = check_nl(str[fd]);
	new_line = ft_calloc(sizeof(char), idx_newline + 2);
	if (!new_line)
		return (NULL);
	i = -1;
	while (++i <= idx_newline)
		new_line[i] = str[fd][i];
	nl_bzero(&str[fd], idx_newline);
	if (!*new_line)
		free_null(&str[fd]);
	return (new_line);
}

/*int main ()
{
	char *str;

	int	fd;
	fd = open("fd7.txt", O_RDONLY);
	str = get_next_line(fd);
	printf("\n %s", str);
	free(str);
	close(fd);

	//fd = open("fd7.txt", O_RDONLY);
	str = get_next_line(fd);
	printf("\n %s", str);
	free(str);
	close(fd);

	return (0);
}

int	main()
{
	char	*stringa;
	int		fd;

	fd = open("fd3.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("NO");
		return (1);
	}
	int i = 0;
	stringa = get_next_line(fd);
	printf("[%d]%s\n",i++, stringa);
	while (stringa)
	{
		free(stringa);
		stringa = get_next_line(fd);
		printf("[%d]%s\n",i++, stringa);
	}
	free(stringa);
	// stringa = get_next_line(fd);
	// printf("[%d]%s\n",i++, stringa);

	// stringa = get_next_line(fd);
	// printf("[%d]%s\n",i++, stringa);

	// stringa = get_next_line(fd);
	// printf("[%d]%s\n",i++, stringa);
}*/
