/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:40:01 by mabrigo           #+#    #+#             */
/*   Updated: 2025/04/23 16:17:25 by damoncad         ###   ########.fr       */
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

# define TILE_SIZE 32
# define MINIMAP_SIZE 8

# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define WHITE 0xFFFFFF
# define PURPLE 0x800080
# define BLACK 0x000000

# define PI 3.14159265
# define FOV (PI / 3)
# define NUM_RAYS 100
# define RS 0.04f

typedef struct s_raycasting_shit
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	ray_x;
	double	ray_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		texture_index;
	float	wall_x;
	int		tex_x;
}	t_raycasting_shit;

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
	float	rx;
	float	ry;
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
	t_raycasting_shit	*ps;
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
void	draw_map(t_game *game, t_map_data *map);
void	paint_floor_ceiling(t_game *game, int floor, int ceiling);
void	draw_floor_ceiling(t_game *game, t_map_data *map);
void 	draw_meme_gun(t_game *game);
int		draw_loop(t_game *game);


//free_shit.c
void	free_matrix(char **map);
void	free_map_textures(t_map_data *map);
void	free_map(t_map_data *map);
void	free_textures(t_game *game);
void	free_game_resources_help(t_game *game);
void	free_game_resources(t_game *game);


//init.c
void	load_texture(t_game *game, t_textures *texture, char *path);
void 	init_textures(t_game *game, t_map_data *map);
void	init_map(t_map_data *map);
void	init_player(t_player *player, t_map_data *map, int offset_x, int offset_y);
void	init_game(char *name_win, t_game *game, t_map_data *map);
//key_events.c
void	key_press_help(int keycode, t_player *player);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
int		close_window(void *param);
//parsing.c
int		is_empty_line(char *str);
int		skip_spaces_check_sign(char *str, int *i);
int		process_digit_and_spaces(char *str, int *i, int *digit_found, int *in_number);
int		check_single_value(char *str);
int 	rgb_char_to_int(int *rgb_values, char **input);
int		count_check_rgb_values(char **splitted);
int		*parse_rgb_values(char *str);
void	assign_texture(char **txtr, char *value, char *err_msg);
void 	handle_target_error(int fd, t_map_data *map, char *message);
int 	check_fc_format(char *fc, int fd, t_map_data *map);
int 	**get_target_color(int i, char *str, t_map_data *map);
void 	handle_parse_error(int fd, t_map_data *map, char *msg);
void	parse_floor_ceiling(int i, char *str, t_map_data *map, int fd);
int		is_valid_config_line(char *str);
void	parse_if_config_done(char *line, int *map_start_line, int current_line, t_map_data *map, int fd);
void	parse_config_line(char *str, t_map_data *map, int fd);
int		is_map_line(char *str);
char	**load_map(char *av, int *map_start_line);
void	parse_file(char **av, int fd, t_map_data *map);
//player
float	get_direction(t_player *player, char c);
bool	is_valid_position(t_map_data *map, float x, float y);
void	move_player(t_player *player, t_game *game);
//rotate_that_booty
void    rotate_point(t_player *player, float center_x, float center_y, float angle);
//map_checks.c
int		map_empty_lines(char **world);
int		map_valid_char(char **world, int i, int player);
void	get_line_data(t_line *line, char *str);
int		check_cardinals(char **world, int i, int j);
int		is_map_closed(char **world, t_line *line);
int		check_map(char **world);
//raycasting.c
int 	get_texture_pixel(t_textures *texture, int x, int y);
void	raycasting(t_game *game);
void	init_raycasting_shit(t_raycasting_shit *ps);
//utils.c
int		my_strchr(char *s, int c);
char	*trim_end_spaces(char *s);
char	*strcmp_from_i(int i, char *src);
int		count_lines(char *av, int fd);
char 	*trim_newline(char *line);
int		get_texture_pixel(t_textures *texture, int x, int y);
//test mappa tonda
void	draw_square(int x, int y, int size, t_game *game, int color);

#endif