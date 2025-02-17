/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:40:59 by mabrigo           #+#    #+#             */
/*   Updated: 2023/10/25 20:50:33 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
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
