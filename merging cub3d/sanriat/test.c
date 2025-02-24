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
	if (keycode == LEFT)
		player->dir -= 0.1f;
	if (keycode == RIGHT)
		player->dir += 0.1f;
	if (keycode == ESC)
	{
		free_game_resources(game);
		printf("fine programma;)\n");
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

// void	init_player(t_player *player)
// {
// 	player->x = WIDTH / 2;
// 	player->y = HEIGHT / 2;
// 	player->key_up = false;
// 	player->key_down = false;
// 	player->key_left = false;
// 	player->key_right = false;
// }


void	init_player(t_player *player, char **map, int offset_x, int offset_y)
{
	int	i;
	int	j;

	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;

	i = 0;
	while(map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'N') //giocatore posizionato nella mappa
			{
				player->x = (float)(j * TILE_SIZE + offset_x + (TILE_SIZE / 2));
				player->y = (float)(i * TILE_SIZE + offset_y + (TILE_SIZE / 2));
				player->dir = PI / 2; //guarda in alto

				//direzione iniziale
				player->dir_x = 0.0f;
				player->dir_y = -1.0f;

				//piano della camera(modifica il FOV)
				player->plane_x = 0.66f;	//0.66 valore standard per il fov
				player->plane_y = 0.0f;

				map[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
	player->x = (float)(WIDTH / 2);
	player->y = (float)(HEIGHT / 2);
	player->dir_x = 1.0f;
	player->dir_y = 0.0f;
	player->plane_x = 0.0f;
	player->plane_y = 0.66f;
	printf("Posizione non trovata sulla mappa, posizionato al centro dello schermo\n");
}



void	move_player(t_player *player)
{
	int	speed;

	speed = 3.0f; //usando un float per avere una velocità più fluida(piu comoda pare a me)
	if (player->key_up && player->y > 0)
		player->y -= speed;
	if (player->key_down && player->y < HEIGHT - 10)
		player->y += speed;
	if (player->key_left && player->x > 0)
		player->x -= speed;
	if (player->key_right && player->x < WIDTH - 10)
		player->x += speed;
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

	// calcolo l'offset della mappa per poterlo mandare a player
	//in modo tale da avere la posizione corretta del character
	game->map_width = (ft_strlen(game->map[0]) - 1);
	game->map_height = 0;
	while (game->map[game->map_height] != NULL)
		game->map_height++;

	game->offset_x = (WIDTH - game->map_width * TILE_SIZE) / 2;
	game->offset_y = (HEIGHT - game->map_height * TILE_SIZE) / 2;

	init_player(game->player, game->map, game->offset_x, game->offset_y);
	game->mlx = mlx_init();
	mlx_get_screen_size(game->mlx, &screen_width, &screen_height);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "CUB3D");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp,
			&game->size_line, &game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

int	not_valid_char(char c)
{
	if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E' && c != 'W')
	{
		return (1);
	}
	return (0);
}

//	DA AGGIUNGERE SE LA MAPPA E' CHIUSA E CONTROLLARE SE TUTTI I BLOCCHI
//SONO RAGGIUNGIBILI (PEZZI DI MAPPA AL DI FUORI DELLA MAPPA)
int	check_map(char **map)
{
	int	i;
	int	j;
	
	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j + 1] != '\0')
		{
			if (not_valid_char(map[i][j]))
			{
				printf("Errore: carattere non valido nella mappa\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	close_window(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (game)
	{
		free_game_resources(game);
	}
	printf("fine programma;)\n");
	exit (0);
	return (0);
}

int	draw_loop(t_game *game)
{
	//t_player *player;

	//player = game->player;
	move_player(game->player);
	
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);

	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
			&game->endian);
	
	draw_map(game);
	//draw_square(player->x, player->y, 15, game, GREEN);
	draw_player(game, game->player, 15, GREEN);

	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

int	main ()
{
	t_game		game;
	
	game.map = load_map("map.txt");
	if (!game.map)
	{
		printf("Errore in load_map\n");
		return (1);
	}
	if (check_map(game.map) != 0)
	{
		printf("La mappa non è valida\n");
		return (1);
	}
	printf("Mappa caricata correttamente! Iniziamo il gioco...\n");
	init_game(&game);
	draw_map(&game);

	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop(game.mlx);

	//free_game_resources(&game);

	return (0);
}
