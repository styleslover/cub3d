/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 21:32:43 by mabrigo           #+#    #+#             */
/*   Updated: 2023/11/25 16:02:20 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

int	ft_printf(const char *str, ...);
int	ft_putchar_fd(char c, int fd);
int	ft_putstr_fd(char *s);
int	ft_putunsigned_fd(unsigned int n, int fd);
int	ft_putnbr_fd(int n, int fd);
int	ft_print_hex(unsigned int nbr, char c);
int	ft_ptr_ptr(unsigned long long ptr);

#endif