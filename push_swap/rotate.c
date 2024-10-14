/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 21:17:38 by mabrigo           #+#    #+#             */
/*   Updated: 2024/09/02 09:15:32 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate(t_list **lst)
{
	t_list	*first;
	t_list	*last;

	if (!lst || !(*lst) || !(*lst)->next)
		return ;
	first = *lst;
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = first;
	first->prev = last;
	*lst = (*lst)->next;
	(*lst)->prev = NULL;
	first->next = NULL;
}

void	ra(t_list **a, bool flag)
{
	rotate(a);
	if (!flag)
		write(1, "ra\n", 3);
}

void	rb(t_list **b, bool flag)
{
	rotate(b);
	if (!flag)
		write(1, "rb\n", 3);
}

void	rr(t_list **a, t_list **b, bool flag)
{
	rotate(a);
	rotate(b);
	if (!flag)
		write(1, "rr\n", 3);
}
