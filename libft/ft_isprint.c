/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:45:53 by mabrigo           #+#    #+#             */
/*   Updated: 2023/10/25 20:50:37 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c > 31 && c < 127)
		return (1);
	return (0);
}

/*int	main()
{
	printf("valore = %d\n", ft_isprint('\n'));
	printf("valore = %d\n", ft_isprint('3'));
	printf("valore = %d\n", ft_isprint('B'));
}	*/
