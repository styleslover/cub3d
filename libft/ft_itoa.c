/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 20:53:30 by damoncad          #+#    #+#             */
/*   Updated: 2025/04/09 19:07:34 by damoncad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbr_len(long n)
{
	int	i;

	i = 0;
	if (n <= 0)
	{
		n *= -1;
		i++;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		n_len;
	long	n_long;

	n_long = n;
	n_len = nbr_len(n_long);
	str = malloc((n_len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	if (n_long == 0)
		str[0] = '0';
	if (n_long < 0)
	{
		n_long *= -1;
		str[0] = '-';
	}
	str[n_len] = '\0';
	while (n_long > 0)
	{
		str[n_len-- - 1] = (n_long % 10) + 48;
		n_long /= 10;
	}
	return (str);
}
