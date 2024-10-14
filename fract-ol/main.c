/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:15:24 by mabrigo           #+#    #+#             */
/*   Updated: 2024/06/06 18:28:05 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	is_number(char *nbr)
{
	int	i;
	int	dot;

	i = 0;
	dot = 0;
	if (nbr[i] && (nbr[i] == '+' || nbr[i] == '-'))
		i++;
	while (nbr[i])
	{
		if (nbr[i] >= '0' && nbr[i] <= '9')
			i++;
		else if (nbr[i] == '.')
		{
			if (dot > 0)
				return (0);
			dot++;
			i++;
		}
		else
			return (0);
	}
	return (1);
}

static int	params_check(char *arg1, char *arg2)
{
	if ((is_number(arg1) == 1 && is_number(arg2) == 1))
		return (0);
	return (1);
}

static void	error_msg(char *message, int fd)
{
	ft_putstr_fd(message, fd);
	exit (EXIT_FAILURE);
}

int	main(int ac, char **av)
{
	t_fractal	fractal;

	if ((!(ft_strncmp(av[1], "Mandelbrot", 10)) && (ac == 2)))
		fractal.name = av[1];
	else if (!(ft_strncmp(av[1], "Julia", 5)) && (ac == 4))
	{
		if (params_check(av[2], av[3]) == 0)
		{
			fractal.name = av[1];
			fractal.julia_x = atodbl(av[2]);
			fractal.julia_y = atodbl(av[3]);
		}
		else
			error_msg(ERROR_MSG, STDERR_FILENO);
	}
	else
		error_msg(ERROR_MSG, STDERR_FILENO);
	init_fractal(&fractal);
	render_fractal(&fractal);
	mlx_loop(fractal.connection);
	return (0);
}
