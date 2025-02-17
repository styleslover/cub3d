/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 18:40:31 by mabrigo           #+#    #+#             */
/*   Updated: 2023/10/25 20:51:50 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		i;

	dup = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (dup == NULL)
		return (dup);
	else
	{
		i = 0;
		while (s[i] != '\0')
		{
			dup[i] = s[i];
			i++;
		}
		dup[i] = '\0';
		return (dup);
	}
}

/*int	main() {
	const char	*s;
	char	*dup;
	
	s = "ciao";
	dup = strdup(s);
	
	if (dup == NULL)
		printf("error");
	printf("%s", dup);
	
	//free(dup);
	
	return 0;
}*/
