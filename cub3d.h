/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:25:03 by mabrigo           #+#    #+#             */
/*   Updated: 2025/02/12 21:37:29 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include <X11/X.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>

# define WIDTH 1820
# define HEIGHT 780

# define W 119
# define A 97
# define S 115
# define D 100
# define ESC 65307

# define PI 3.14159265359

typedef struct s_player
{
	float	x;
	float	y;

	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
}		t_player;

typedef struct s_game
{
	void		*mlx; // Puntatore alla connessione con la libreria MiniLibX
	void		*win; // Puntatore alla finestra creata con MiniLibX
	void		*img; // Puntatore all'immagine (buffer di disegno)

	char		*data; // Array di byte che rappresenta i pixel dell'immagine
	int			bpp; // "Bits Per Pixel" → Numero di bit per ogni pixel
	int			size_line; // Numero di byte per ogni riga dell'immagine
	int			endian; // Specifica l'ordine dei byte (Big endian o Little endian)

	t_player	*player;
}			t_game;



#endif