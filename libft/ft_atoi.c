/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:25:52 by damoncad          #+#    #+#             */
/*   Updated: 2023/12/13 20:08:56 by damoncad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	a;
	int	segno;
	int	resu;

	a = 0;
	segno = 1;
	resu = 0;
	while (str[a] == ' ' || (str[a] >= 9 && str[a] <= 13))
		a++;
	if (str[a] == '-' || str[a] == '+')
	{
		if (str[a] == '-')
			segno *= -1;
		a++;
	}
	while (str[a] >= '0' && str[a] <= '9')
	{
		resu = (str[a] - '0') + (resu * 10);
		a++;
	}
	return (resu * segno);
}
