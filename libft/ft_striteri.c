/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 17:09:05 by mabrigo           #+#    #+#             */
/*   Updated: 2023/10/25 20:51:54 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

/*void my_func(unsigned int i, char *str)
{
 	printf("Character at index %u is %c\n", i, *str);
}

int main()
{
 	char str[] = "ciao belli";
	ft_striteri(str, my_func);
 	return (0);
}*/