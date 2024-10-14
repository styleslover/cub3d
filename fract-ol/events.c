/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:59:57 by mabrigo           #+#    #+#             */
/*   Updated: 2024/06/06 18:27:13 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	close_handler(t_fractal *fractal)
{
	mlx_destroy_image(fractal->connection, fractal->img.ptr_image);
	mlx_destroy_window(fractal->connection, fractal->win);
	mlx_destroy_display(fractal->connection);
	free(fractal->connection);
	exit (EXIT_SUCCESS);
}

int	key_handler(int keysym, t_fractal *fractal)
{
	if (keysym == XK_Escape)
		close_handler(fractal);
	else if (keysym == XK_Left)
		fractal->shift_x -= (0.1 * fractal->zoom);
	else if (keysym == XK_Right)
		fractal->shift_x += (0.1 * fractal->zoom);
	else if (keysym == XK_Up)
		fractal->shift_y += (0.1 * fractal->zoom);
	else if (keysym == XK_Down)
		fractal->shift_y -= (0.1 * fractal->zoom);
	else if (keysym == XK_equal)
		fractal->iter_def += 10;
	else if (keysym == XK_minus)
		fractal->iter_def -= 10;
	render_fractal(fractal);
	return (0);
}

int	mouse_handler(int button, int x, int y, t_fractal *fractal)
{
	(void)x;
	(void)y;
	if (button == Button5)
	{
		fractal->zoom *= 1.05;
	}
	else if (button == Button4)
	{
		fractal->zoom *= 0.95;
	}
	render_fractal(fractal);
	return (0);
}
