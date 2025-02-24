/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 20:17:50 by damoncad          #+#    #+#             */
/*   Updated: 2023/12/14 20:21:35 by damoncad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char  *s1, char  *set)
{
	size_t	a;
	size_t	b;
	char	*str;

	str = 0;
	if (s1 != 0 && set != 0)
	{
		a = 0;
		b = ft_strlen(s1);
		while (s1[a] && ft_strchr(set, s1[a]))
			a++;
		while (s1[b - 1] && ft_strchr(set, s1[b - 1]) && b > a)
			b--;
		str = (char *)malloc(sizeof(char) * (b - a + 1));
		if (str)
			ft_strlcpy(str, &s1[a], b - a + 1);
	}
	return (str);
}
