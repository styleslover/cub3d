/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:57:37 by mabrigo           #+#    #+#             */
/*   Updated: 2025/02/18 21:04:42 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

char	*nl_strcat(char *str1, char *str2);
char	*get_string(char **str, int fd);
char	*get_next_line(int fd);
int		check_nl(char *str);
int		nl_strlen(char *str);
char	*nl_bzero(char **s, int n);
void	*nl_calloc(int nmemb, int size);

#endif