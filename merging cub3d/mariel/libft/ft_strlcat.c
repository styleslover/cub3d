/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 21:14:30 by mabrigo           #+#    #+#             */
/*   Updated: 2023/11/03 18:35:22 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	d_len;
	size_t	s_len;
	size_t	i;
	size_t	j;

	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	if (size <= d_len)
		return (s_len + size);
	i = d_len;
	j = 0;
	while (i < size - 1 && src[j] != 0)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (d_len + s_len);
}

/*int	main(void)
{
	char	d[10] = "cane";
	char	s[10] = "pazzo";


	printf("%zu", ft_strlcat(d, s, 7));
	printf("\n%s\n", d);

	char	d1[10] = "cane";
	char	s1[10] = "pazzo";
	

	printf("%zu", ft_strlcat(d1, s1, 0));
	printf("\n%s", d1);
}*/
