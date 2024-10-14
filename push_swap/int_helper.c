/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:05:37 by mabrigo           #+#    #+#             */
/*   Updated: 2024/09/02 09:18:16 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	verify(char **argv, char **split_argv)
{
	int	i;

	i = 1;
	while (argv[i] != NULL)
	{
		if (!is_number(argv[i]) || is_duplicate(argv, argv[i], i))
		{
			if (split_argv != NULL)
				ft_free_split(split_argv);
			return (1);
		}
		if (ft_easy_atol(argv[i]) > INT_MAX || ft_easy_atol(argv[i]) < INT_MIN)
		{
			if (split_argv != NULL)
				ft_free_split(split_argv);
			write(2, "Error\n", 6);
			return (1);
		}
		i++;
	}
	return (0);
}

void	what_sort(t_list **a, t_list **b)
{
	if (stack_len(*a) == 2)
		sa(a, 0);
	else if (stack_len(*a) == 3)
		sort_three(a);
	else
		sort_stacks(a, b);
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	if (split == NULL)
		return ;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

long	ft_easy_atol(const char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\f' || str[i] == '\v')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			sign = -1;
		}
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
