/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:57:49 by mabrigo           #+#    #+#             */
/*   Updated: 2023/11/15 20:15:19 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*new_elem;
	void	*dup;

	new = NULL;
	while (lst)
	{
		dup = f(lst->content);
		new_elem = ft_lstnew(dup);
		if (!new_elem)
		{
			ft_lstclear(&new, del);
			del(dup);
			return (NULL);
		}
		ft_lstadd_back(&new, new_elem);
		lst = lst->next;
	}
	return (new);
}
