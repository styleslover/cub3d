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
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <X11/X.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <math.h>

# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define WHITE 0xFFFFFF

# define WIDTH 1280
# define HEIGHT 720
# define TILE_SIZE 64

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define ESC 65307

# define PI 3.14159265359f

// typedef struct s_ray
// {
//     double camera_x;        // Posizione del raggio nel piano della camera (-1 sinistra, 1 destra)
    
//     double ray_dir_x;       // Direzione del raggio lungo l'asse X
//     double ray_dir_y;       // Direzione del raggio lungo l'asse Y

//     int map_x;              // Coordinata X della cella della mappa in cui si trova il raggio
//     int map_y;              // Coordinata Y della cella della mappa in cui si trova il raggio

//     double side_dist_x;     // Distanza dal bordo della cella alla prima intersezione con una parete (X)
//     double side_dist_y;     // Distanza dal bordo della cella alla prima intersezione con una parete (Y)

//     double delta_dist_x;    // Distanza necessaria per attraversare completamente una cella lungo X
//     double delta_dist_y;    // Distanza necessaria per attraversare completamente una cella lungo Y

//     int step_x;             // Direzione del passo lungo X (-1 = sinistra, 1 = destra)
//     int step_y;             // Direzione del passo lungo Y (-1 = su, 1 = giù)

//     int hit;                // Flag per indicare se il raggio ha colpito una parete (1 = sì, 0 = no)
//     int side;               // Indica se il raggio ha colpito una parete verticale (1) o orizzontale (0)

//     double perp_wall_dist;  // Distanza perpendicolare dalla posizione del player alla parete colpita
// } t_ray;

typedef struct s_player
{
	float	x;			// Posizione X del giocatore
	float	y;			// Posizione Y del giocatore
	float	dir;		// Angolo di rotazione (in radianti)

	float	dir_x;		// Direzione X (vettore direzione)
	float	dir_y;		// Direzione Y (vettore direzione)
	float	plane_x;	// Piano della camera X (per la prospettiva)
	float	plane_y;	// Piano della camera Y (per la prospettiva)

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
	char		**map;
	int			offset_x;
	int			offset_y;
	int			map_width;
	int			map_height;
}			t_game;

void	my_pixel_put(int x, int y, t_game *game, int color);
int	count_lines(char *filename);

//free_shit.c
void	free_map(char **map);
void	free_mlx(t_game *game);
void	free_game_resources(t_game *game);

//draw_picasso.c
void	draw_square(int x, int y, int size, t_game *game, int color);
void	draw_player(t_game *game, t_player *player, int size, int color);
void	draw_grid(t_game *game, int tile_size);
void	draw_map(t_game *game);
void	draw_direction_line(t_game *game, t_player *player, int length, int color);

//rotate_that_booty.c
void    rotate_point(float *x, float *y, float center_x, float center_y, float angle);

#endif