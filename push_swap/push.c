/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 21:17:16 by mabrigo           #+#    #+#             */
/*   Updated: 2024/09/02 09:15:32 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push(t_list **src, t_list **dest)
{
	t_list	*tmp;

	if (*src == NULL)
		return ;
	tmp = (*src);
	*src = (*src)->next;
	if (*src)
		(*src)->prev = NULL;
	if (!*dest)
	{
		(*dest) = tmp;
		(*dest)->next = NULL;
		(*dest)->prev = NULL;
	}
	else
	{
		tmp->next = (*dest);
		(*dest)->prev = tmp;
		tmp->prev = NULL;
		(*dest) = tmp;
	}
}

void	pa(t_list **b, t_list **a, bool flag)
{
	push(a, b);
	if (!flag)
		write(1, "pa\n", 3);
}

void	pb(t_list **a, t_list **b, bool flag)
{
	push(b, a);
	if (!flag)
		write(1, "pb\n", 3);
}
