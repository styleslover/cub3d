/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:40:01 by mabrigo           #+#    #+#             */
/*   Updated: 2025/02/21 12:49:33 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx-linux/mlx.h"
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <math.h>
# include <X11/X.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

# define WIDTH 1820
# define HEIGHT 780

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363

# define ESC 65307

# define TILE_SIZE 64

# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define WHITE 0xFFFFFF

# define PI 3.14159265359

typedef struct s_player
{
	float	x;
	float	y;
	float	dir;

	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;

	float	dir_x;		// Direzione X (vettore direzione)
	float	dir_y;		// Direzione Y (vettore direzione)
	float	plane_x;	// Piano della camera X (per la prospettiva)
	float	plane_y;	// Piano della camera Y (per la prospettiva)
}		t_player;

typedef struct s_map_data
{
	int			fd;
	int			win_width;
	int			win_height;

	char		*north_txtr;
	char		*west_txtr;
	char		*south_txtr;
	char		*east_txtr;

	char		*ceiling_color;
	char		*floor_color;
}				t_map_data;

typedef struct s_game
{
	void		*mlx; // Puntatore alla connessione con la libreria MiniLibX
	void		*win; // Puntatore alla finestra creata con MiniLibX
	void		*img; // Puntatore all'immagine (buffer di disegno)

	char		*data; // Array di byte che rappresenta i pixel dell'immagine
	int			bpp; // "Bits Per Pixel" → Numero di bit per ogni pixel
	int			size_line; // Numero di byte per ogni riga dell'immagine
	int			endian; // Specifica l'ordine dei byte (Big endian o Little endian)

	char		**map;
	int			offset_x;
	int			offset_y;
	int			map_width;
	int			map_height;
	t_player	*player;
}			t_game;


#endif