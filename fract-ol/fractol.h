/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:28:23 by mabrigo           #+#    #+#             */
/*   Updated: 2024/06/06 18:38:57 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>

# define ERROR_MSG "\033[1;31mInvalid input, please enter one of the following:\
				\n\t~./fractol Mandelbrot\
				\n\t~./fractol Julia <value_1> <value_2>\n\033[1;31m"
# define JULIA_ERR "\033[1;31mJulia's parameters must be a number!\n\033[1;31m"
# define WIDTH 800
# define HEIGHT 800

# define BLACK       		0x000000
# define WHITE       		0xFFFFFF
# define RED         		0xFF0000
# define NEON_GREEN  		0x39FF14
# define NEON_PINK   		0xFF1493
# define NEON_BLUE   		0x4D4DFF
# define NEON_ORANGE 		0xFF9933
# define ELECTRIC_BLUE 		0x7DF9FF
# define HOT_PINK    		0xFF69B4
# define SHOCKING_PINK 		0xFC0FC0
# define ELECTRIC_PURPLE 	0xBF00FF
# define ELECTRIC_RED    	0xFF003F

typedef struct s_complex
{
	double	x;
	double	y;
}			t_complex;

typedef struct s_image
{
	void	*ptr_image;
	char	*pixels;
	int		bits_pxls;
	int		endian;
	int		line_len;
}			t_image;

typedef struct s_fractal
{
	void	*connection;
	void	*win;
	t_image	img;
	char	*name;

	double	hypotenuse;
	int		iter_def; //the more the merrier
	double	shift_x;
	double	shift_y;

	double	zoom;

	double	julia_x;
	double	julia_y;

	double	mouse_x;
	double	mouse_y;
}			t_fractal;

void		init_fractal(t_fractal *fractal);
void		render_fractal(t_fractal *fractal);
double		map(double unscaled_num, double new_min,
				double new_max, double old_max);
t_complex	complex_sum(t_complex v1, t_complex v2);
t_complex	complex_square(t_complex v);
int			close_handler(t_fractal *fractal);
int			key_handler(int keysym, t_fractal *fractal);
int			mouse_handler(int button, int x, int y, t_fractal *fractal);

#endif
