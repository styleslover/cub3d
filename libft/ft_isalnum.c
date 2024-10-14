/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:35:46 by mabrigo           #+#    #+#             */
/*   Updated: 2023/10/25 20:49:57 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (((c > 64 && c < 91) || (c > 96 && c < 123)) || (c > 47 && c < 58))
		return (1);
	else
		return (0);
}

/*int	main()
{
	printf("valore = %d\n", ft_isalnum(' '));
	printf("valore = %d\n", ft_isalnum('3'));
	printf("valore = %d\n", ft_isalnum('B'));
}*/	
