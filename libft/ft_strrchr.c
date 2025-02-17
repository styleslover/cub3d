/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 21:16:01 by mabrigo           #+#    #+#             */
/*   Updated: 2023/11/03 19:11:26 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*res;

	res = NULL;
	while (*s != '\0')
	{
		if (*s == (unsigned char)c)
			res = (char *)s;
		s++;
	}
	if ((unsigned char)c == 0)
		return ((char *)s);
	return (res);
}

/*int	main()
{
	char s[50] = "hola soy dora";
    
	if (ft_strrchr(s, 's') == NULL)
		printf ("letter not found");
	else
		puts (ft_strrchr(s, 's'));
}*/
