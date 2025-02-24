/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariel <mariel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:40:01 by mabrigo           #+#    #+#             */
/*   Updated: 2025/02/25 00:09:17 by mariel           ###   ########.fr       */
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
	char		**world;
	int			fd;
	int			win_width;
	int			win_height;

	int			map_width;
	int			map_height;
	int			offset_x;
	int			offset_y;

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

	t_player	*player;
	t_map_data	*map;
}			t_game;

//cub3d.c
int	print_error(char *str);

//draw.c
void	my_pixel_put(int x, int y, t_game *game, int color);
void	draw_direction_line(t_game *game, t_player *player, int length, int color);
void	draw_player(t_game *game, t_player *player, int size, int color);
void	draw_grid(t_map_data *map, int tile_size);
void	draw_map(t_map_data *map);
int		draw_loop(t_game *game);

//free_shit.c
void	free_map(char **map);
void	free_mlx(t_game *game);
void	free_game_resources(t_game *game);

//init.c
void	init_map(t_map_data *map);
void	init_player(t_player *player, t_map_data *map, int offset_x, int offset_y);
void	init_game(t_game *game, t_map_data *map);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
int		close_window(void *param);

//parsing.c
char	*strcmp_from_i(int i, char *src);
void	parse_config_line(char *str, t_map_data *map);
int		is_map_line(char *str);
int		count_lines(char **av, int fd);
char	**load_map(char **av, int fd);
void	parse_file(char **av, int fd, t_map_data *map);

//move_player
void	move_player(t_player *player);
void    rotate_point(float *x, float *y, float center_x, float center_y, float angle);


#endif