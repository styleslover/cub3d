/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 18:15:08 by mabrigo           #+#    #+#             */
/*   Updated: 2023/10/25 20:49:20 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//nmemb = elementi; size = dimensione
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (ptr);
	else
	{
		ft_bzero(ptr, nmemb * size);
		return (ptr);
	}
}

/*int main() {
    int *ptr;
    int n = 5;

    // Utilizza la tua implementazione di ft_calloc
    ptr = (int *)ft_calloc(n, sizeof(int));

    if (ptr == NULL) {
        printf("Errore nell'allocazione di memoria.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", ptr[i]);  // Stampa zeri
    }

    free(ptr);

    return 0;
}*/
