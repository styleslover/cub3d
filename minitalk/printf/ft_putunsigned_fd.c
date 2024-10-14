/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 21:46:02 by mabrigo           #+#    #+#             */
/*   Updated: 2023/11/25 12:42:23 by mabrigo          ###   ########.fr       */
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
		n /= 10;
		i++;
	}
	return (i);
}

int	ft_putunsigned_fd(unsigned int n, int fd)
{
	unsigned long	num;

	num = n;
	if (num > 9)
		ft_putunsigned_fd((num / 10), fd);
	ft_putchar_fd((num % 10) + 48, fd);
	return (length(n));
}

/*int	main()
{
	ft_putunsigned_fd(-5, 1);
	return 0;
}*/