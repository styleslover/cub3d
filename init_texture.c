/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrigo <mabrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:27:23 by mabrigo           #+#    #+#             */
/*   Updated: 2025/04/27 20:15:17 by mabrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_errors(t_game *game, char *path, int fd, const char *msg)
{
	if (fd >= 0)
		close(fd);
	if (path)
		free(path);
	free_textures(game);
	free_map(game->map);
	free_game_resources_help(game);
	clear_gnl();
	if (msg)
		printf("%s", (char *)msg);
	exit(1);
}

void	init_textures(t_game *game, t_map_data *map)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->textures[i].img = NULL;
		i++;
	}
	load_texture(game, &game->textures[0], map->north_txtr);
	load_texture(game, &game->textures[1], map->south_txtr);
	load_texture(game, &game->textures[2], map->east_txtr);
	load_texture(game, &game->textures[3], map->west_txtr);
}

void	is_texture_empty(t_game *game, int fd, char *clean_path)
{
	char	buffer[5];
	int		bytes_read;

	bytes_read = read(fd, buffer, 4);
	if (bytes_read > 0)
		buffer[bytes_read] = '\0';
	else
		buffer[0] = '\0';
	if (bytes_read <= 0)
	{
		handle_errors(game, clean_path, fd,
			"Error: Texture file is empty.\n");
	}
}

void	validate_texture_file(t_game *game, char *clean_path)
{
	int	fd;

	fd = open(clean_path, __O_DIRECTORY);
	if (fd != -1)
	{
		handle_errors(game, clean_path, fd,
			"Error\nTexture path is a directory.\n");
	}
	fd = open(clean_path, O_RDONLY);
	if (fd == -1)
	{
		handle_errors(game, clean_path, fd,
			"Error\nCould not open texture file.\n");
	}
	is_texture_empty(game, fd, clean_path);
	close(fd);
}

void	load_texture(t_game *game, t_textures *texture, char *path)
{
	char	*clean_path;

	clean_path = ft_strtrim(path, "\t\n\r");
	if (!clean_path)
		handle_errors(game, NULL, -1,
			"Error\nMemory allocation failed for texture path.\n");
	validate_texture_file(game, clean_path);
	texture->img = mlx_xpm_file_to_image(game->mlx, clean_path,
			&texture->width, &texture->height);
	if (!texture->img)
	{
		handle_errors(game, clean_path, -1, "Error\nCould not load texture.\n");
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->line_length, &texture->endian);
	free(clean_path);
}
