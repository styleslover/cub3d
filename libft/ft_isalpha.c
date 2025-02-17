/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:39:06 by mabrigo           #+#    #+#             */
/*   Updated: 2023/10/26 22:45:03 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123))
		return (1);
	else
		return (0);
}

/*int	main()
{
	printf("valore = %d\n", ft_isdigit('2'));
	printf("valore = %d\n", ft_isdigit('a'));
	printf("valore = %d\n", ft_isdigit('B'));
}	*/
