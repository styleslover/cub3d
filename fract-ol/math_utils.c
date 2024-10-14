/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:10:00 by mabrigo           #+#    #+#             */
/*   Updated: 2024/05/22 18:40:16 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	map(double unscaled_num, double new_min, double new_max, double old_max)
{
	return ((new_max - new_min) * (unscaled_num) / (old_max) + new_min);
}

t_complex	complex_sum(t_complex v1, t_complex v2)
{
	t_complex	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	return (result);
}

//z = x + yi tale che i^2 = -1
//quadrato di tutto cio sotto z^2 = x^2 + xyi - (yi)^2
t_complex	complex_square(t_complex v)
{
	t_complex	result;

	result.x = (v.x * v.x) - (v.y * v.y);
	result.y = 2 * v.x * v.y;
	return (result);
}
