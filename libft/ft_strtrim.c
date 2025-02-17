/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 21:48:33 by mabrigo           #+#    #+#             */
/*   Updated: 2023/11/01 21:18:19 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*out;
	long	start;
	long	end;

	out = (char *)s1;
	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (*s1 && ft_strchr(set, out[start]) != NULL)
		start++;
	while (end > start && ft_strchr(set, s1[end]) != NULL)
		end--;
	if (end < start)
		return (ft_strdup(""));
	out = (char *)malloc(end - start + 2);
	if (out == NULL)
		return (NULL);
	out = (char *)ft_memcpy(out, &s1[start], end - start + 1);
	out[end - start + 1] = '\0';
	return (out);
}

/*int main()
{
    const char *s1;
    const char *set;
    
    s1 = "               ";
    set = "iac";
    
    printf("%s", ft_strtrim(s1, set));
}*/
