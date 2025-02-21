/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:25:03 by mabrigo           #+#    #+#             */
/*   Updated: 2025/02/21 12:30:34 by mabrigo          ###   ########.fr       */
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

# define PI 3.14159265359

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;

	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;

	//bool	left_rot;
	//bool	right_rot;
}		t_player;

typedef struct s_map
{
	int			fd;
	int			map_width;
	int			map_height;

	char		*north_txtr;
	char		*west_txtr;
	char		*south_txtr;
	char		*east_txtr;

	char		*ceiling_color;
	char		*floor_color;
}				t_map;

typedef struct s_game
{
	void		*mlx; // Puntatore alla connessione con la libreria MiniLibX
	void		*win; // Puntatore alla finestra creata con MiniLibX
	void		*img; // Puntatore all'immagine (buffer di disegno)

	char		*data; // Array di byte che rappresenta i pixel dell'immagine
	int			bpp; // "Bits Per Pixel" → Numero di bit per ogni pixel
	int			size_line; // Numero di byte per ogni riga dell'immagine
	int			endian; // Specifica l'ordine dei byte (Big endian o Little endian)

	int			offset_x;
	int			offset_y;
	t_player	*player;
}			t_game;

void	my_pixel_put(int x, int y, t_game *game, int color);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
int		draw_loop(t_game *game);

void	init_game(t_game *game);

//map
char	*strcmp_from_i(int i, char *src);
void	parse_config_line(char *str, t_map *map);
int		is_map_line(char *str);
void	parse_file(int fd, t_map *map);


void	init_player(t_player *player);
void	draw_player(t_game *game, t_player *player, int size, int color);
void	turn_player(t_player *player);
void	move_player(t_player *player);

#endif