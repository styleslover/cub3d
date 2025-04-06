/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:40:01 by mabrigo           #+#    #+#             */
/*   Updated: 2025/04/06 16:41:02 by mabrigo          ###   ########.fr       */
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
# define SPACE 32

# define ESC 65307

# define TILE_SIZE 32
#define MINIMAP_SIZE 8  // Scala la mappa al 20% della grandezza originale


# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define WHITE 0xFFFFFF
# define PURPLE 0x800080
# define BLACK 0x000000

# define PI 3.14159265
# define FOV (PI / 3)
# define NUM_RAYS 100
# define ROTASPEED 0.04f

typedef struct s_textures
{
	void    *img;
    char    *addr;
    int     width;
    int     height;
    int     bpp;
    int     line_length;
    int     endian;
} t_textures;

typedef struct s_player
{
	float	x;
	float	y;
	int		tile_x;
	int		tile_y;
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
	int			offset_minimap_x;
	int			offset_minimap_y;

	char		*north_txtr;
	char		*west_txtr;
	char		*south_txtr;
	char		*east_txtr;

	int			*ceiling_color;
	int			*floor_color;
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

	int			screen_w;
	int			screen_h;
	float		cos_rot_speed;
	float		sin_rot_speed;

	t_textures	textures[4];
	t_player	*player;
	t_map_data	*map;
}			t_game;

typedef struct s_line_data
{
	int	start;
	int	end;
}	t_line;


//cub3d.c
int	print_error(char *str);
int	check_filename(char *av);

//draw.c
void	my_pixel_put(int x, int y, t_game *game, int color);
void	draw_direction_line(t_game *game, t_player *player, int length, int color);
void	draw_square(int x, int y, int size, t_game *game, int color);
void	draw_player(t_game *game, t_player *player, int size, int color);
void	draw_grid(t_game *game, t_map_data *map, int tile_size);
void	draw_map(t_game *game, t_map_data *map);
void	paint_floor_ceiling(t_game *game, int floor, int ceiling);
void	draw_floor_ceiling(t_game *game, t_map_data *map);
void 	draw_meme_gun(t_game *game);
int		draw_loop(t_game *game);

//free_shit.c
void	free_matrix(char **map);
void	free_map(t_map_data *map);
void	free_mlx(t_game *game);
void	free_game_resources(t_game *game);

//init.c
void	load_texture(t_game *game, t_textures *texture, char *path);
void 	init_textures(t_game *game, t_map_data *map);
void	init_map(t_map_data *map);
void	init_player(t_player *player, t_map_data *map, int offset_x, int offset_y);
void	init_game(char *name_win, t_game *game, t_map_data *map);

//key_events.c
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
int		close_window(void *param);

//parsing.c
int		is_empty_line(char *str);
int		*parse_rgb_values(char *str);
void	assign_texture(char **txtr, char *value, char *err_msg);
void	parse_floor_ceiling(int i, char *str, t_map_data *map);
void	parse_config_line(char *str, t_map_data *map);
int		is_map_line(char *str);
char	**load_map(char *av, int *map_start_line);
void	parse_file(char **av, int fd, t_map_data *map);

//player
float	get_direction(t_player *player, char c);
bool	is_valid_position(t_map_data *map, float x, float y);
void	move_player(t_player *player, t_game *game); //a che serve

//rotate_that_booty
void    rotate_point(float *x, float *y, float center_x, float center_y, float angle);

//map_checks.c
int		map_empty_lines(char **world);
int		map_valid_char(char **world);
void	get_line_data(t_line *line, char *str);
int		check_cardinals(char **world, int i, int j);
int		is_map_closed(char **world, t_line *line);
int		check_map(char **world);

//raycasting.c
int 	get_texture_pixel(t_textures *texture, int x, int y);
void	raycasting(t_game *game);
//void 	raylaser(t_game *game, t_player *player, float end_x, float end_y);

//utils.c
int		my_strchr(char *s, int c);
char	*trim_end_spaces(char *s);
char	*strcmp_from_i(int i, char *src);
int		count_lines(char *av, int fd);
char 	*trim_newline(char *line);


//int get_texture_color(t_game *game, int tex_x, int tex_y, int side);
int get_texture_pixel(t_textures *texture, int x, int y);


//test mappa
void draw_line(int x0, int y0, int x1, int y1, t_game *game, int color);
void draw_circle(int center_x, int center_y, int radius, t_game *game, int color);
void draw_player_minimap(t_game *game, int center_x, int center_y, int size, int color);







//test mappa tonda
void draw_player_minimap(t_game *game, int center_x, int center_y, int size, int color);
void draw_square(int x, int y, int size, t_game *game, int color);
void draw_circle_outline(int center_x, int center_y, int radius, t_game *game, int color);
void draw_player_direction(t_game *game, int center_x, int center_y, int length, int color);







#endif