/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:40:01 by mabrigo           #+#    #+#             */
/*   Updated: 2025/04/26 14:40:12 by damoncad         ###   ########.fr       */
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

typedef struct s_parse_state
{
    int config_done;
    int map_start_line;
    int current_line;
} t_parse_state;

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
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_length;
	int		endian;
} 	t_textures;

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
	void				*mlx;
	void				*win;
	void				*img;

	char				*data;
	int					bpp;
	int					size_line;
	int					endian;
	int					color_player;
	int					color_map;

	int					screen_w;
	int					screen_h;
	float				cos_rot_speed;
	float				sin_rot_speed;

	t_textures			textures[4];
	t_player			*player;
	t_map_data			*map;
	t_raycasting_shit	*ps;
}			t_game;

typedef struct s_line_data
{
	int	start;
	int	end;
}	t_line;

//cub3d.c
int		print_error(char *str);
int		check_filename(char *av);
void	free_game_resources(t_game *game);

//draw.c //OK!
void	my_pixel_put(int x, int y, t_game *game, int color);
void	paint_floor_ceiling(t_game *game, int floor, int ceiling);
void	draw_floor_ceiling(t_game *game, t_map_data *map);
int		draw_loop(t_game *game);

//draw_map //OK!
int		get_tile_color(char tile);
void	calculate_minimap_offset(t_game *game, t_map_data *map);
void	draw_map_row(t_game *game, t_map_data *map, int i);
void	color_map(t_map_data *map, t_game *game, int color, int i);
void	draw_map(t_game *game, t_map_data *map);

//draw_player.c //DRAW_SQUARE HA TROPPI PARAMETRI
void	draw_square(int x, int y, int size, t_game *game);
void	draw_player(t_game *game, t_player *player, int size);

//free_shit.c //OK!
void	free_matrix(char **map);
void	free_map_textures(t_map_data *map);
void	free_map(t_map_data *map);
void	free_textures(t_game *game);
void	free_game_resources_help(t_game *game);

//init.c
void	init_map(t_map_data *map);
void	init_screen_and_offsets(t_game *game, t_map_data *map);
void	init_raycasting_memory(t_game *game);
void	init_window_and_image(t_game *game, char *name_win);
void	init_game(char *name_win, t_game *game, t_map_data *map);

//init_player.c //OK!
void	init_player_memory(t_game *game);
void	find_player_position(t_player *player, t_map_data *map);
void	set_player_position(t_player *player, t_map_data *map,
			int offset_x, int offset_y);
void	init_player(t_player *player, t_map_data *map,
			int offset_x, int offset_y);
void init_game_pointers(t_game *game);

//init_texture.c //OK!
void	handle_errors(t_game *game, char *path, int fd, const char *msg);
void	is_texture_empty(t_game *game, int fd, char *clean_path);
void	validate_texture_file(t_game *game, char *clean_path);
void	load_texture(t_game *game, t_textures *texture, char *path);
void	init_textures(t_game *game, t_map_data *map);

//key_events.c //OK!
void	key_press_help(int keycode, t_player *player);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
int		close_window(void *param);

//parsing.c
int		is_valid_config_line(char *str);
void	parse_config_line(char *str, t_map_data *map, int fd);
void	process_line(char *line, t_map_data *map, int fd, t_parse_state *state);
void	parse_file(char **av, int fd, t_map_data *map);
void	handle_config_line(char *line, t_map_data *map,
			int fd, int *config_done);

//parsing_valid_path.c
char	*ft_strstr(const char *haystack, const char *needle);
void	free_split(char **split);
int		check_xpm_values(int *values, char **split);
int		process_xpm_dimension_line(char *line, int *values);
int		find_xpm_header(int fd, int *values);


//parsing_texture.c
void	assign_texture(char **txtr, char *value, char *err_msg);
int		validate_xpm_header(char *texture_path);
int		is_valid_texture_path(char *path);
void	handle_texture_error(t_map_data *map, char *str, int fd);
void	handle_texture(t_map_data *map, int fd, char *str, int offset);

//parsing_fc.c
int		check_fc_format(char *fc, int fd, t_map_data *map);
int		**get_target_color(int i, char *str, t_map_data *map);
void	handle_invalid_color(int fd, t_map_data *map);
void	parse_floor_ceiling(int i, char *str, t_map_data *map, int fd);

//parsing_fc_rgb.c
int		process_digit_and_spaces(char *str, int *i,
			int *digit_found, int *in_number);
int		check_single_value(char *str);
int		rgb_char_to_int(int *rgb_values, char **input);
int		count_check_rgb_values(char **splitted);
int		*parse_rgb_values(char *str);

//parsing_map.c
int		handle_map_line(char *line, int current_line, int *map_start_line);
void	handle_map_error(char *line, int fd, t_map_data *map);
void	calculate_map_dimensions(t_map_data *map);
void	load_and_check_map(char **av, t_map_data *map, int map_start_line);

//parsing_starter_map.c
int		is_map_line(char *str);
char	**set_map(int map_start_line, char *av, int *fd);
void	skip_to_map_start(int fd, int map_start_line);
int		get_map(char **map, int fd, int map_start_line);
char	**load_map(char *av, int map_start_line);


//parsing_utils.c
int		is_empty_line(char *str);
int		is_valid_config_line(char *str);
void	check_empty_file(int current_line, t_map_data *map);
void	handle_config_error(int fd, t_map_data *map, char *message);
int		skip_spaces_check_sign(char *str, int *i);

//player.C //OK!
void	set_east_west_direction(t_player *player, char c);
void	set_north_south_direction(t_player *player, char c);
void	get_direction(t_player *player, char c);
bool	is_valid_position(t_map_data *map, float x, float y);
void	move_player(t_player *player, t_game *game);

//player_moves.c //OK!
void	move_forward(t_player *player, t_map_data *map);
void	move_backward(t_player *player, t_map_data *map);
void	move_left(t_player *player, t_map_data *map);
void	move_right(t_player *player, t_map_data *map);
void	rotate_point(t_player *player, float center_x,
			float center_y, float angle);

//map_checks.c //OK!
int		check_cardinals(char **world, int i, int j);
int		is_map_closed(char **world, t_line *line);
int		check_map(char **world);

//map_checks_utils.c
int		map_empty_lines(char **world);
int		map_valid_char(char **world, int i, int player);
void	get_line_data(t_line *line, char *str);

//raycasting.c
int		get_texture_pixel(t_textures *texture, int x, int y);
void	perform_dda(t_raycasting_shit *a, t_map_data *map);
void	set_texture_data(t_raycasting_shit *a, t_game *game);
void	draw_column(t_raycasting_shit *a, t_game *game, int x);
void	raycasting(t_game *game);

//raycasting_utils.c
void	init_raycasting_shit(t_raycasting_shit *ps);
void	init_ray(t_raycasting_shit *a, t_game *game, int x);
void	calc_step_and_side_dist(t_raycasting_shit *a);
void	calc_wall_data(t_raycasting_shit *a, t_game *game);


//utils.c
int		my_strchr(char *s, int c);
char	*trim_end_spaces(char *s);
char	*strcmp_from_i(int i, char *src);
int		count_lines(char *av, int fd);
char	*trim_newline(char *line);
int		get_texture_pixel(t_textures *texture, int x, int y);


#endif