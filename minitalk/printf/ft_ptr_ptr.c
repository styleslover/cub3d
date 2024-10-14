/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 21:41:31 by mabrigo           #+#    #+#             */
/*   Updated: 2023/11/28 19:44:51 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*int	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}*/

static int	length(unsigned long n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		n /= 16;
		i++;
	}
	return (i);
}

void	ft_put_ptr(unsigned long nbr)
{
	if (nbr >= 16)
	{
		ft_put_ptr(nbr / 16);
		ft_put_ptr(nbr % 16);
	}
	else
	{
		if (nbr <= 9)
			ft_putchar_fd((nbr + '0'), 1);
		else
		{
			ft_putchar_fd((nbr - 10 + 'a'), 1);
		}
	}
}

int	ft_ptr_ptr(unsigned long long ptr)
{
	int	len;

	len = 0;
	if (ptr == 0)
	{
		len += write(1, "(nil)", 5);
		return (5);
	}
	len += write(1, "0x", 2);
	if (ptr != 0)
	{
		ft_put_ptr(ptr);
		len += length(ptr);
	}
	return (len);
}

/*int	main()
{
	ft_ptr_ptr(10);
	printf("\n%x", 10);
}*/