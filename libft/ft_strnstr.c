/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 19:29:16 by damoncad          #+#    #+#             */
/*   Updated: 2025/04/23 16:24:19 by damoncad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr( char *big, char *little, size_t len)
{
	size_t	i;
	size_t	n;
	size_t	little_len;

	i = 0;
	n = 0;
	little_len = ft_strlen(little);
	if (little[0] == '\0')
		return ((char *)big);
	while (i < len && big[i])
	{
		while (big[i + n] == little[n] && n + i < len)
		{
			if (n >= little_len - 1)
				return ((char *)&big[i]);
			n++;
		}
		n = 0;
		i++;
	}
	return (0);
}
