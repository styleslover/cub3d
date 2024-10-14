/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:05:59 by mabrigo           #+#    #+#             */
/*   Updated: 2024/05/03 19:46:41 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# ifndef EOT
#  define EOT '\0'
# endif

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define BOLD "\x1b[1m"
# define RESET_COLOR "\x1b[0m" 

# include "libft/libft.h"
# include "printf/ft_printf.h"
# include <sys/types.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

void	send_signal(int pid, char character);
void	send_signal(int pid, char character);

#endif