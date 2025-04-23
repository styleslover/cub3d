/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:43:07 by damoncad          #+#    #+#             */
/*   Updated: 2025/04/23 16:28:37 by damoncad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp( void *s1, void *s2, size_t n)
{
	char	*str1;
	char	*str2;
	size_t	a;

	a = 0;
	str1 = (char *)s1;
	str2 = (char *)s2;
	while (a < n)
	{
		if (str1[a] != str2[a])
			return ((unsigned char)str1[a] - (unsigned char)str2[a]);
		a++;
	}
	return (0);
}
