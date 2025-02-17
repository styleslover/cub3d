/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:48:10 by mabrigo           #+#    #+#             */
/*   Updated: 2023/10/25 20:51:12 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t len)
{
	char	*p;

	p = (char *)s;
	while (len > 0)
	{
		*p = (char)c;
		len--;
		p++;
	}
	return (s);
}

/*int main()
{
  char str[50] = "cazzo ne so";
  ft_memset(str, '*', 5);
  puts(str);
}*/
