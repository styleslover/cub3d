/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 21:17:27 by mabrigo           #+#    #+#             */
/*   Updated: 2023/10/25 20:46:01 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	long	i;
	long	nbr;
	int		segno;

	i = 0;
	nbr = 0;
	segno = 1;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			segno *= -1;
		i++;
	}
	while (nptr[i] > 47 && nptr[i] < 58)
	{
		nbr = nbr * 10 + (nptr[i] - 48);
		i++;
	}
	return (nbr * segno);
}

/*int main()
{
    printf("%d", ft_atoi("  	-aa5245 155sd664"));

    return 0;
}*/
