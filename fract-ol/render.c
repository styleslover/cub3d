/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 19:19:15 by mabrigo           #+#    #+#             */
/*   Updated: 2024/05/30 20:53:04 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
MANDELBROT
	- z = z^2 + c
	- z = (0, 0) INIZIALMENTEEE
	- c punto "reale"

JULIA
	./fractol Julia <real> <im>
	- z = pixel_point + constant
*/

static void	my_pixel_put(int x, int y, t_image *img, int color)
{
	int	offset;

	offset = (y * img->line_len) + (x * (img->bits_pxls / 8));
	*(unsigned int *)(img->pixels + offset) = color;
}

static void	mandel_or_julia(t_complex *z, t_complex *c, t_fractal *fractal)
{
	if (!ft_strncmp(fractal->name, "Julia", 5))
	{
		c->x = fractal->julia_x;
		c->y = fractal->julia_y;
	}
	else
	{
		c->x = z->x;
		c->y = z->y;
	}
}

static void	handle_pxl(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	z.x = (map(x, -2, +2, WIDTH) * fractal->zoom) + fractal->shift_x;
	z.y = (map(y, +2, -2, HEIGHT) * fractal->zoom) + fractal->shift_y;
	i = 0;
	mandel_or_julia(&z, &c, fractal);
	while (i < fractal->iter_def)
	{
		z = complex_sum(complex_square(z), c);
		if ((z.x * z.x) + (z.y * z.y) > fractal->hypotenuse)
		{
			color = map(i, BLACK, WHITE, fractal->iter_def);
			my_pixel_put(x, y, &fractal->img, color);
			return ;
		}
		++i;
	}
	my_pixel_put(x, y, &fractal->img, NEON_GREEN);
}

void	render_fractal(t_fractal *fractal)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			handle_pxl(x, y, fractal);
		}
	}
	mlx_put_image_to_window(fractal->connection, fractal->win,
		fractal->img.ptr_image, 0, 0);
}
