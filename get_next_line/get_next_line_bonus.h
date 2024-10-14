/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 21:07:58 by mabrigo           #+#    #+#             */
/*   Updated: 2023/12/22 21:09:00 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
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
void	*ft_calloc(int nmemb, int size);

#endif