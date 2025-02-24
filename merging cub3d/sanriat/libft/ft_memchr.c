/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 21:19:50 by damoncad          #+#    #+#             */
/*   Updated: 2023/12/14 20:32:49 by damoncad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr( void *s, int c, size_t n)
{
	char	*str;
	size_t	a;

	a = 0;
	str = (char *)s;
	while (a < n)
	{
		if ((unsigned char)str[a] == (unsigned char)c)
			return ((char *)s + a);
		a++;
	}
	return (NULL);
}
