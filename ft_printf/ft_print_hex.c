/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 21:09:42 by mabrigo           #+#    #+#             */
/*   Updated: 2023/11/28 19:38:32 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	length(unsigned int n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 16;
		i++;
	}
	return (i);
}

void	ft_hex(unsigned int nbr, char format)
{
	if (nbr >= 16)
	{
		ft_hex(nbr / 16, format);
		ft_hex(nbr % 16, format);
	}
	else
	{
		if (nbr <= 9)
			ft_putchar_fd((nbr + '0'), 1);
		else
		{
			if (format == 'x')
				ft_putchar_fd((nbr - 10 + 'a'), 1);
			if (format == 'X')
				ft_putchar_fd((nbr - 10 + 'A'), 1);
		}
	}
}

int	ft_print_hex(unsigned int nbr, char format)
{
	if (nbr == 0)
		write(1, "0", 1);
	else
		ft_hex(nbr, format);
	return (length(nbr));
}
