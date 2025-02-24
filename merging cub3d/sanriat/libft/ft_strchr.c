/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 21:08:40 by damoncad          #+#    #+#             */
/*   Updated: 2023/12/13 21:15:43 by damoncad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr( char *s, int c)
{
	int	a;

	a = 0;
	while ((s[a] != (char)c) && (s[a] != '\0'))
		a++;
	if (s[a] == (char)c)
		return ((char *)&s[a]);
	return (0);
}
