/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 19:27:56 by damoncad          #+#    #+#             */
/*   Updated: 2023/12/21 19:27:58 by damoncad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest,  void *src, size_t n)
{
	char		*dest_ptr;
	 char	*src_ptr;
	size_t		i;

	dest_ptr = (char *)dest;
	src_ptr = ( char *)src;
	if (dest_ptr == src_ptr)
		return (dest);
	if (src_ptr < dest_ptr)
	{
		i = n + 1;
		while (--i > 0)
			dest_ptr[i - 1] = src_ptr[i - 1];
	}
	else
	{
		i = -1;
		while (++i < n)
			dest_ptr[i] = src_ptr[i];
	}
	return (dest);
}
