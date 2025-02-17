/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:55:52 by damoncad          #+#    #+#             */
/*   Updated: 2024/03/09 14:44:47 by damoncad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <fcntl.h> 

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*initialize_buffer(int fd);
size_t	ft_str_newline(char *buffer);
size_t	ft_nl(char *buffer);
char	*resize_buffer(char *buffer);
char	*extract_line_part(char *buffer);
char	*resize_and_copy_buffer(char *buffer, char *line_part);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_strlen(char *buffer);

#endif