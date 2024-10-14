/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:04:12 by mabrigo           #+#    #+#             */
/*   Updated: 2024/06/07 18:31:22 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	malloc_error(void)
{
	ft_putstr_fd("MALLOC ERROR", STDERR_FILENO);
	exit(1);
}

static void	data_init(t_fractal *fractal)
{
	fractal->hypotenuse = 4;
	fractal->iter_def = 100;
	fractal->shift_x = 0.0;
	fractal->shift_y = 0.0;
	fractal->zoom = 1.0;
}

static void	event_init(t_fractal *fractal)
{
	mlx_hook(fractal->win, KeyPress, KeyPressMask, key_handler, fractal);
	mlx_hook(fractal->win, ButtonPress, ButtonPressMask,
		mouse_handler, fractal);
	mlx_hook(fractal->win, DestroyNotify, StructureNotifyMask,
		close_handler, fractal);
}

void	init_fractal(t_fractal *fractal)
{
	fractal->connection = mlx_init();
	if (!fractal->connection)
		malloc_error();
	fractal->win = mlx_new_window(fractal->connection,
			WIDTH, HEIGHT, fractal->name);
	if (!fractal->win)
	{
		mlx_destroy_display(fractal->connection);
		free(fractal->connection);
		malloc_error();
	}
	fractal->img.ptr_image = mlx_new_image(fractal->connection, WIDTH, HEIGHT);
	if (!fractal->img.ptr_image)
	{
		mlx_destroy_window(fractal->connection, fractal->win);
		mlx_destroy_display(fractal->connection);
		free(fractal->connection);
		malloc_error();
	}
	fractal->img.pixels = mlx_get_data_addr(fractal->img.ptr_image,
			&fractal->img.bits_pxls, &fractal->img.line_len,
			&fractal->img.endian);
	event_init(fractal);
	data_init(fractal);
}
