/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 21:11:00 by mabrigo           #+#    #+#             */
/*   Updated: 2023/11/16 18:35:01 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*free_matrix(char **matrix, int j)
{
	while (--j >= 0)
		free(matrix[j]);
	free(matrix);
	return (NULL);
}

static int	counter(char const *s, char c)
{
	int	i;

	if (!*s)
		return (0);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			i++;
		while (*s != c && *s)
			s++;
	}
	return (i);
}

static char	*word_strdup(const char *s, int start, int end)
{
	char	*dup;
	int		i;

	i = 0;
	dup = malloc(sizeof(char) * (end - start + 1));
	if (!dup)
		return (NULL);
	while (start < end)
		dup[i++] = s[start++];
	dup[i] = '\0';
	return (dup);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	i;
	size_t	j;
	int		index;

	split = malloc(sizeof(char *) * (counter(s, c) + 1));
	if (!s || !split)
		return (NULL);
	i = -1;
	j = 0;
	index = -1;
	while (++i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			split[j++] = word_strdup(s, index, i);
			if (!split[j - 1])
				return (free_matrix(split, j));
			index = -1;
		}
	}
	split[j] = NULL;
	return (split);
}

/*int main()
{
	char *str;
	char	**matrice;

	str = "i 4lh fghf";
	char	c = ' ';
	int i = 0;
	
	matrice = ft_split(str, c);
	while (matrice[i] != NULL)         "ciao    fdg dfg dfg dfg dfg "  
	{
		printf("%s\n", matrice[i]);
		i++;
	}
	return(0);
}*/
