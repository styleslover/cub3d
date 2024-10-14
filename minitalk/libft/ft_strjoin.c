/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 21:29:07 by mabrigo           #+#    #+#             */
/*   Updated: 2023/11/01 19:17:41 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*out;
	long	i;
	long	j;

	out = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (out == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		out[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		out[i] = s2[j];
		i++;
		j++;
	}
	out[i] = '\0';
	return (out);
}

/*int	main()
{
	char const	*s1;
	char const	*s2;
	
	s1 = "ho voglia di ";
	s2 = "pane";
	printf("%s", ft_strjoin(s1, s2));
	
	return (0);
}*/
