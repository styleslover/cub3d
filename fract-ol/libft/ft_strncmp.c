/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 21:16:18 by mabrigo           #+#    #+#             */
/*   Updated: 2024/05/19 15:50:03 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (NULL == s1 || NULL == s2 || n <= 0)
		return (0);
	while (i < n && (s1[i] != 0 || s2[i] != 0))
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

/*int	main()
{
	const char	s1[50] = "mamma";
	const char	s2[49] = "mammella";

	printf("%d", ft_strncmp(s1, s2, 6));
}*/
