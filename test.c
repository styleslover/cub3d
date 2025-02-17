/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:36:54 by mabrigo           #+#    #+#             */
/*   Updated: 2025/02/12 21:47:48 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Permette di colorare un singolo pixel nell'immagine.
// Calcola indice del pixel nell'array data
// Controllo per evitare di uscire dallo schermo
// Impostazione del colore (blu, verde e rosso)
void	my_pixel_put(int x, int y, t_game *game, int color)
{
	int	index;

	index = y * game->size_line + x * game->bpp / 8;
	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

int	key_press(int keycode, t_game *game)
{
	t_player	*player;

	player = game->player;
	if (keycode == W)
		player->key_up = true;
	if (keycode == S)
		player->key_down = true;
	if (keycode == A)
		player->key_left = true;
	if (keycode == D)
		player->key_right = true;
	if (keycode == ESC)
	{
		mlx_destroy_window(game->mlx, game->win);
		exit (0);
	}
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	t_player	*player;

	player = game->player;
	if (keycode == W)
		player->key_up = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == D)
		player->key_right = false;
	return (0);
}

void	init_player(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
}

void	draw_player(t_game *game, t_player *player, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_pixel_put(player->x + j, player->y + i, game, color);
			j++;
		}
		i++;
	}
}

void	draw_square(int x, int y, int size, t_game *game, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_pixel_put(x + j, y + i, game, color);
			j++;
		}
		i++;
	}
}

void	move_player(t_player *player)
{
	int	speed;

	speed = 5;
	if (player->key_up && player->y > 0)
		player->y -= speed;
	if (player->key_down && player->y < HEIGHT - 10)
		player->y += speed;
	if (player->key_left && player->x > 0)
		player->x -= speed;
	if (player->key_right && player->x < WIDTH - 10)
		player->x += speed;
}

void	draw_map(t_game *game)
{
	char	**map;
	int		color;
	int		i;
	int		j;
	int		tile_size;
	int		offset_x;
	int		offset_y;
	int		map_width;
	int		map_height;

	map = game->map;
	tile_size = 64;

	map_width = ft_strlen(map[0]);
	map_height = 0;
	while (map[map_height] != NULL)
		map_height++;

	offset_x = (WIDTH - map_width * tile_size) / 2;
	offset_y = (HEIGHT - map_height * tile_size) / 2;
	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == '1')
				color = 0x0000FF;			
			else
				color = 0x00FF00;
			draw_square(j * tile_size + offset_x, i * tile_size, tile_size + offset_y, game, color);
			j++;
		}
		i++;
	}
}

int	draw_loop(t_game *game)
{
	t_player *player;

	player = game->player;
	move_player(player);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
			&game->endian);
	draw_map(game);
	draw_player(game, player, 10, 0xFF00FF);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

int	count_lines(char *filename)
{
	int		fd;
	int		lines;
	char	*line;

	lines = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	while ((line = get_next_line(fd)))
	{
		lines++;
		free(line);
	}
	close(fd);
	return (lines);
}

// Funzione per caricare la mappa
char	**load_map(char *filename)
{
	int		fd;
	int		i;
	int		lines;
	char	**map;

	lines = count_lines(filename);
	if (lines <= 0)
		return (NULL);
	map = malloc((lines + 1) * sizeof(char *));  // +1 per NULL finale
	if (!map)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		free(map);
		return (NULL);
	}
	i = 0;
	while (i < lines)
	{
		map[i] = get_next_line(fd);
		if (!map[i])  // Se get_next_line fallisce
		{
			while (i > 0)
				free(map[--i]);
			free(map);
			close(fd);
			return (NULL);
		}
		i++;
	}
	map[i] = NULL;  // Terminatore NULL per l'array di stringhe
	close(fd);
	return (map);
}


void	init_game(t_game *game)
{
	int	screen_width;
	int	screen_height;

	game->player = malloc(sizeof(t_player));
	if (!game->player)
	{
		perror("Errore in malloc player\n");
		exit (1);
	}
	init_player(game->player);
	game->mlx = mlx_init();
	mlx_get_screen_size(game->mlx, &screen_width, &screen_height);

	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "CUB3D");
	
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp,
			&game->size_line, &game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

int	main ()
{
	t_game		game;
	int i;

	i = 0;
	game.map = load_map("map.txt");
	if (!game.map)
	{
		printf("Errore in load_map\n");
		return (1);
	}
	init_game(&game);
	draw_map(&game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);

	free(game.player);
	while (game.map[i])
	{
		free(game.map[i]);
		i++;
	}
	free(game.map);
	return (0);
}
