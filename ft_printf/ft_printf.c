/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 21:11:51 by mabrigo           #+#    #+#             */
/*   Updated: 2023/11/28 19:40:58 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static int	check_format(char c, va_list arg)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += ft_putchar_fd(va_arg(arg, int), 1);
	else if (c == 's')
		count += ft_putstr_fd(va_arg(arg, char *));
	else if (c == 'p')
		count += ft_ptr_ptr(va_arg(arg, long long));
	else if (c == 'd')
		count += ft_putnbr_fd(va_arg(arg, int), 1);
	else if (c == 'i')
		count += ft_putnbr_fd(va_arg(arg, int), 1);
	else if (c == 'u')
		count += ft_putunsigned_fd(va_arg(arg, unsigned int), 1);
	else if (c == 'x' || c == 'X')
		count += ft_print_hex(va_arg(arg, unsigned int), c);
	else if (c == '%')
		count += write(1, "%", 1);
	return (count);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	va_list	arg;
	int		count;

	i = 0;
	count = 0;
	va_start(arg, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			count += check_format(str[i], arg);
		}
		else
			count += ft_putchar_fd(str[i], 1);
		i++;
	}
	va_end(arg);
	return (count);
}

/*int	main()
{
	int i = ft_printf("mo:%x\n", -1);
	printf("mio: %d\n", i);
	int j = printf("og:%x\n", -1);
	printf("or: %d", j);
	return (0);
}*/
