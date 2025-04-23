/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 20:06:25 by damoncad          #+#    #+#             */
/*   Updated: 2025/04/23 16:25:46 by damoncad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stddef.h>

int		ft_isalnum(unsigned char c);
int		ft_strlen( char *s);
int		ft_isascii(int c);
int		ft_isalpha(int c);
int		ft_atoi( char *nptr);
int		ft_isdigit(int c);
int		ft_isprint(int c);
size_t	ft_strlcpy(char *dest, char *src, size_t size);
void	*ft_memset(void *dest, int c, size_t count);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, void *src, size_t n);
size_t	ft_strlcat(char *dst, char *src, size_t size);
int		ft_strncmp( char *s1, char *s2, size_t n);
void	*ft_memmove(void *s1, void *s2, size_t n);
int		ft_tolower(int c);
int		ft_toupper(int c);
char	*ft_strchr( char *s, int c);
void	*ft_memchr( void *s, int c, size_t n);
void	*ft_calloc(size_t count, size_t n);
int		ft_memcmp( void *s1, void *s2, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strdup( char *s);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strmapi(char *s, char (*f)(unsigned int, char));
char	*ft_strnstr( char *big, char *little, size_t n);
char	*ft_strtrim(char *s1, char *set);
char	*ft_strrchr( char *s, int c);
char	**ft_split(char *s, char c);
char	*ft_itoa(int n);
char	*ft_substr( char *s, unsigned int start, size_t len);

#endif