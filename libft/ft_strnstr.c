/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 21:17:15 by mabrigo           #+#    #+#             */
/*   Updated: 2023/10/25 21:04:30 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	len_little;
	char	*cbig;

	i = 0;
	len_little = ft_strlen(little);
	cbig = (char *)big;
	if (len_little == 0 || big == little)
		return (cbig);
	else
	{
		while (cbig[i] != '\0' && i < len)
		{
			j = 0;
			while (cbig[i + j] != '\0' && little[j] != '\0'
				&& cbig[i + j] == little[j] && i + j < len)
				j++;
			if (j == len_little)
				return (cbig + i);
			i++;
		}
		return (NULL);
	}
}

/*int main()
{
    const char big[50] = "hola soy dora y me gusta ...";
    const char small[50] = "ciao";
    
    ;
    printf("%s", ft_strnstr(big, small, 10));

    return 0;
}
		*/	
