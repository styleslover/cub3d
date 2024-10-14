/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atodbl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:36:29 by mabrigo           #+#    #+#             */
/*   Updated: 2024/06/03 18:50:19 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//converts to long double
double	atodbl(char *s)
{
	long	int_part;
	double	dec_part;
	double	pow;
	int		sign;

	int_part = 0;
	dec_part = 0;
	sign = 1;
	pow = 1;
	while ((*s >= 9 && *s <= 13) || *s == 32)
		s++;
	while (*s == '+' || *s == '-')
		if (*s++ == '-')
			sign *= -1;
	while (*s != '.' && *s)
		int_part = (int_part * 10) + (*s++ - 48);
	if (*s == '.')
		s++;
	while (*s)
	{
		pow /= 10;
		dec_part = dec_part + (*s++ - 48) * pow;
	}
	return ((int_part + dec_part) * sign);
}
