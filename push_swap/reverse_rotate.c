/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 21:17:26 by mabrigo           #+#    #+#             */
/*   Updated: 2024/09/02 09:15:32 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	reverse_rotate(t_list **lst)
{
	t_list	*dupe;
	t_list	*last;

	if (!(*lst) || !((*lst)->next))
		return ;
	last = *lst;
	while (last->next)
		last = last->next;
	dupe = last->prev;
	dupe->next = NULL;
	last->next = *lst;
	(*lst)->prev = last;
	last->prev = NULL;
	*lst = last;
}

void	rra(t_list **a, bool flag)
{
	reverse_rotate(a);
	if (!flag)
		write(1, "rra\n", 4);
}

void	rrb(t_list **b, bool flag)
{
	reverse_rotate(b);
	if (!flag)
		write(1, "rrb\n", 4);
}

void	rrr(t_list **a, t_list **b, bool flag)
{
	reverse_rotate(a);
	reverse_rotate(b);
	if (!flag)
		write(1, "rrr\n", 4);
}
