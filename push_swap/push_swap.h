/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 21:33:45 by mabrigo           #+#    #+#             */
/*   Updated: 2024/09/02 09:25:24 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdbool.h>
# include <limits.h>
# include "./libft/libft.h"
# include <stdio.h>

typedef struct s_list
{
	int				nbr;
	int				index;
	int				push_cost;
	bool			medium;
	bool			cheapest;
	struct s_list	*target_node;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

int		is_number(char *str);
int		is_duplicate(char **argv, char *current_arg, int current_index);
void	free_stack(t_list **stack);

void	ft_free_split(char **split);
int		verify(char **argv, char **split_argv);
void	what_sort(t_list **a, t_list **b);
long	ft_easy_atol(const char *str);

void	init_stack_a(t_list **a, char **argv);
char	**split(char *s, char c);

void	init_nodes_a(t_list *a, t_list *b);
void	init_nodes_b(t_list *a, t_list *b);
void	current_index(t_list *stack);
void	set_cheapest(t_list *stack);
t_list	*get_cheapest(t_list *stack);
void	pre_push(t_list **s, t_list *n, char c);

int		stack_len(t_list *stack);
t_list	*find_last(t_list *stack);
bool	stack_sorted(t_list *stack);
t_list	*find_min(t_list *stack);
t_list	*find_max(t_list *stack);

void	sa(t_list **a, bool flag);
void	sb(t_list **b, bool flag);
void	ss(t_list **a, t_list **b, bool flag);
void	ra(t_list **a, bool flag);
void	rb(t_list **b, bool flag);
void	rr(t_list **a, t_list **b, bool flag);
void	rra(t_list **a, bool flag);
void	rrb(t_list **b, bool flag);
void	rrr(t_list **a, t_list **b, bool flag);

void	pa(t_list **b, t_list **a, bool flag);
void	pb(t_list **a, t_list **b, bool flag);

void	min_on_top(t_list **a);
void	move_a_to_b(t_list **a, t_list **b);
void	move_b_to_a(t_list **a, t_list **b);
void	rotate_both(t_list **a, t_list **b, t_list *cheapest_node);
void	reverse_rotate_both(t_list **a, t_list **b, t_list *cheapest_node);

void	sort_three(t_list **a);
void	sort_stacks(t_list **a, t_list **b);

#endif