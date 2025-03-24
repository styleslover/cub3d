/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:12:27 by damoncad          #+#    #+#             */
/*   Updated: 2025/03/24 16:28:10 by damoncad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
void	raycasting(t_game *game)
{
	t_player	*player;
	t_map_data	*map;
	int			screen_width;
	int			screen_height;
	int			x;
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	double		ray_pos_x;
	double		ray_pos_y;
	//lunghezza del raggio da un lato all'altro della mappa
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	
	player = game->player;
	map = game->map;
	screen_width = game->screen_w;
	screen_height = game->screen_h;
	x = 0;
	while (x < screen_width)
	{
		//calcola posix e dir del raggio
		camera_x = 2 * x / (double)screen_width - 1;//coor x nello spazio della camera
		ray_dir_x = player->dir_x + player->plane_x * camera_x;
		ray_dir_y = player->dir_y + player->plane_y * camera_x;

		//posizione iniziale raggio
		ray_pos_x = player->x;
		ray_pos_y = player->y;

		//lunghezza del raggio da un lato all'altro della mappa
		delta_dist_x = fabs(1 / ray_dir_x);
		delta_dist_y = fabs(1 / ray_dir_y);
		
		//controlla se il raggio ha colpito una parete
		hit = 0;
		//calcolo il passo e la distanza iniziale
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (ray_pos_x - (int)ray_pos_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = ((int)ray_pos_x + 1.0 - ray_pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (ray_pos_y - (int)ray_pos_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = ((int)ray_pos_y + 1.0 - ray_pos_y) * delta_dist_y;
		}

		//esegue algoritmo DDA(Digital Differential Analyzer)
		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				ray_pos_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				ray_pos_y += step_y;
				side = 1;
			}

			//controlla se il raggio ha colpito una parete
			if (map->world[(int)ray_pos_y][(int)ray_pos_x] == '1')
				hit = 1;
		}

		//calcola la distanza proiettata
		if (side == 0)
			perp_wall_dist = (ray_pos_x - player->x + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (ray_pos_y - player->y + (1 - step_y) / 2) / ray_dir_y;
		
		//calcola l'altezza della riga da disegnare
		int line_height = (int)(screen_height / perp_wall_dist);

		//calcola i punti d'inizio e fine della linea
		int draw_start = -line_height / 2 + screen_height / 2;
        if (draw_start < 0)
            draw_start = 0;
        int draw_end = line_height / 2 + screen_height / 2;
        if (draw_end >= screen_height)
            draw_end = screen_height - 1;

		//colore in base alla direzione
		int color;
		if (side == 1)
			color = 0x808080;
		else
			color = 0xFFFFFF;
		
		int y = draw_start;
		while (y < draw_end)
		{
			//disegna la linea
			my_pixel_put(x, y, game, color);
			y++;
		}
		x++;
	}
}
*/
//DOVREBBE ESSERE QUELLO BUONO
/*
void    raycasting(t_game *game)
{
	t_map_data	*map;
    float   ray_angle;
    float   ray_x;
    float   ray_y;
    float   step_x;
    float   step_y;
    float   pos_x;
    float   pos_y;
    int     i;
    int     map_x;
    int     map_y;

	map = game->map;
    ray_angle = game->player->dir - (FOV / 2);  //inizia dal lato sinistro del FOV
    i = 0;
    while (i < NUM_RAYS)    //lancia un numero fisso di raggi
    {
        //calcolo la direzione del raggio
        ray_x = cosf(ray_angle);
        ray_y = sinf(ray_angle);
        
		//posizione iniziale del raggio (posizione del giocatore)
        pos_x = game->player->x;
        pos_y = game->player->y;

        //passo per il raycasting (piu piccolo per maggiore precisione)
        step_x = ray_x / 512.0f;
        step_y = ray_y / 512.0f;


        //avanza il raggio finche non colpisce un muro
        while (1)
        {
            pos_x += step_x;
            pos_y += step_y;

            //controllo se il raggio ha colpito il muro
            map_x = (int)(pos_x / TILE_SIZE);
            map_y = (int)(pos_y / TILE_SIZE);

            //verifica i limiti della mappa
            if (map_x < 0 || map_x >= map->map_width ||
                    map_y < 0 || map_y >= map->map_height)
                break;
            if (map->world[map_y][map_x] == '1')
                break;
        }
        //disegna la linea del raggio
        draw_direction_line(game, game->player, pos_x, pos_y);
        ray_angle += FOV / NUM_RAYS;    //passa al prossimo raggio
        i++;
    }
}*/





// void raylaser(t_game *game, t_player *player, float end_x, float end_y)
// {
//     float start_x = player->x;
//     float start_y = player->y;

//     // Debug: stampa le coordinate di inizio e fine
//     printf("Start: (%f, %f), End: (%f, %f)\n", start_x, start_y, end_x, end_y);

//     float delta_x = end_x - start_x;
//     float delta_y = end_y - start_y;

//     // Calcola il numero di passi in base alla distanza maggiore tra delta_x e delta_y
//     float steps = fmaxf(fabsf(delta_x), fabsf(delta_y));

//     // Se steps è 0, la linea è solo un punto
//     if (steps == 0)
//     {
//         printf("Error: Line is a single point\n");
//         return;
//     }

//     float step_x = delta_x / steps;
//     float step_y = delta_y / steps;

//     for (int i = 0; i < steps; i++)
//     {
//         int x = (int)(start_x + step_x * i);
//         int y = (int)(start_y + step_y * i);

//         // Debug: stampa le coordinate di ogni punto
//         printf("Drawing pixel at (%d, %d)\n", x, y);

//         // Disegna il pixel solo se è all'interno dei limiti dello schermo
//         if (x >= 0 && x < game->screen_w && y >= 0 && y < game->screen_h)
//         {
//             my_pixel_put(x, y, game, 0xFF0000);  // Colore rosso per i raggi
//         }
//     }
// }




// void raycasting(t_game *game)
// {
//     t_map_data *map = game->map;
//     float fov = 60.0f * (PI / 180.0f);  // Campo visivo in radianti
//     float ray_angle = game->player->dir - (fov / 2);  // Angolo iniziale (lato sinistro del FOV)
//     float angle_increment = fov / NUM_RAYS;  // Incremento angolare tra i raggi
//     int i = 0;

//     while (i < NUM_RAYS)  // Lancia un numero fisso di raggi
//     {
//         // Calcola la direzione del raggio
//         float ray_x = cosf(ray_angle);
//         float ray_y = sinf(ray_angle);

//         // Posizione iniziale del raggio (posizione del giocatore)
//         float pos_x = game->player->x;
//         float pos_y = game->player->y;

//         // Avanza il raggio finché non colpisce un muro
//         // Avanza il raggio finché non colpisce un muro
// 	while (1)
// 	{
//     	pos_x += ray_x * 5.0f;  // Passo più grande (5.0f invece di 1.0f)
//     	pos_y += ray_y * 5.0f;

//     // Controlla se il raggio ha colpito un muro
// 	    int map_x = (int)(pos_x / TILE_SIZE);
//     	int map_y = (int)(pos_y / TILE_SIZE);

//     	if (map_x < 0 || map_x >= map->map_width || map_y < 0 || map_y >= map->map_height)
//         	break;  // Raggio uscito dalla mappa

//     if (map->world[map_y][map_x] == '1')
//     {
//         // Correzione per fermare il raggio esattamente al muro
//         if (ray_x < 0)
//             pos_x += 0.001f;  // Piccola correzione per l'asse x
//         else
//             pos_y += 0.001f;  // Piccola correzione per l'asse y
//         break;  // Raggio ha colpito un muro
//     }
// }


// 		printf("Start: (%f, %f), End: (%f, %f)\n", game->player->x, game->player->y, pos_x, pos_y);

//         // Disegna la linea del raggio in 2D (dal giocatore al punto di intersezione)
//         draw_direction_line(game, game->player, pos_x, pos_y);

//         // Passa al prossimo raggio
//         ray_angle += angle_increment;
//         ray_angle = fmod(ray_angle, 2 * PI);  // Normalizza l'angolo
//         i++;
//     }
// }























// void raycasting(t_game *game) {
//     t_player *player = game->player;
//     int x = 0;

//     player->plane_x = 0.66f * player->dir_y;  // Se dir_y = 0
//     player->plane_y = 0.66f * player->dir_x;  // Se dir_x = 0
//     while (x < game->screen_w) {
//         // Calcola la posizione e la direzione del raggio
//         double camera_x = 2 * x / (double)game->screen_w - 1;
//         double ray_dir_x = player->dir_x + player->plane_x * camera_x;
//         double ray_dir_y = player->dir_y + player->plane_y * camera_x;

//         // Posizione iniziale del raggio (posizione del giocatore)
//         double ray_pos_x = player->x - game->map->offset_x;
//         double ray_pos_y = player->y - game->map->offset_y;

//         // Delta distance e side distance
//         double delta_dist_x = fabs(1 / ray_dir_x);
//         double delta_dist_y = fabs(1 / ray_dir_y);

//         int step_x, step_y;
//         double side_dist_x, side_dist_y;
//         int hit = 0;
//         int side; // 0 = x-side, 1 = y-side

//         // Calcola step e side_dist iniziale
//         if (ray_dir_x < 0) {
//             step_x = -1;
//             side_dist_x = (ray_pos_x - (int)ray_pos_x) * delta_dist_x;
//         } else {
//             step_x = 1;
//             side_dist_x = ((int)ray_pos_x + 1.0 - ray_pos_x) * delta_dist_x;
//         }
//         if (ray_dir_y < 0) {
//             step_y = -1;
//             side_dist_y = (ray_pos_y - (int)ray_pos_y) * delta_dist_y;
//         } else {
//             step_y = 1;
//             side_dist_y = ((int)ray_pos_y + 1.0 - ray_pos_y) * delta_dist_y;
//         }

//         // DDA Algorithm
//         while (hit == 0) {
//             if (side_dist_x < side_dist_y) {
//                 side_dist_x += delta_dist_x;
//                 ray_pos_x += step_x;
//                 side = 0;
//             } else {
//                 side_dist_y += delta_dist_y;
//                 ray_pos_y += step_y;
//                 side = 1;
//             }
//             // Controlla se il raggio ha colpito un muro
//             int map_x = (int)ray_pos_x;
//             int map_y = (int)ray_pos_y;
//             if (map_x < 0 || map_x >= game->map->map_width || 
//                map_y < 0 || map_y >= game->map->map_height)
//                 hit = 1; // Raggio uscito dalla mappa
//             else if (game->map->world[map_y][map_x] == '1') {
//                 hit = 1; // Muro colpito
//             }
//         }

//         // Calcola la distanza corretta (senza fisheye)
//         double perp_wall_dist;
//         if (side == 0) {
//             perp_wall_dist = (ray_pos_x - player->x + (1 - step_x) / 2) / ray_dir_x;
//         } else {
//             perp_wall_dist = (ray_pos_y - player->y + (1 - step_y) / 2) / ray_dir_y;
//         }

//         // Calcola l'altezza della linea da disegnare
//         int line_height = (int)(game->screen_h / perp_wall_dist);
//         int draw_start = -line_height / 2 + game->screen_h / 2;
//         if (draw_start < 0) draw_start = 0;
//         int draw_end = line_height / 2 + game->screen_h / 2;
//         if (draw_end >= game->screen_h) draw_end = game->screen_h - 1;

//         // Scegli il colore in base al lato del muro
//         int color = (side == 1) ? 0x606060 : 0xFFFFFF; // Grigio per y-side, bianco per x-side

//         // Disegna la linea verticale
//         for (int y = draw_start; y < draw_end; y++) {
//             my_pixel_put(x, y, game, color);
//         }
//         x++;
//         printf("Processing column: %d/%d\n", x, game->screen_w);

//     }
// }











#include "cub3d.h"

void raycasting(t_game *game) {
    t_player *p = game->player;
    t_map_data *map = game->map;

    for (int x = 0; x < game->screen_w; x++) {
        // 1. Calcolo direzione del raggio
        double camera_x = 2 * x / (double)game->screen_w - 1; // Range: [-1, 1]
        double ray_dir_x = p->dir_x + p->plane_x * camera_x;
        double ray_dir_y = p->dir_y + p->plane_y * camera_x;

        // 2. Posizione iniziale (in coordinate mappa)
        double ray_x = (p->x - map->offset_x) / TILE_SIZE;
        double ray_y = (p->y - map->offset_y) / TILE_SIZE;

        // 3. DDA Algorithm
        double delta_dist_x = fabs(1 / ray_dir_x);
        double delta_dist_y = fabs(1 / ray_dir_y);
        
        int map_x = (int)ray_x;
        int map_y = (int)ray_y;
        
        double side_dist_x, side_dist_y;
        int step_x, step_y;
        int hit = 0;
        int side; // 0 = x-side, 1 = y-side

        // Calcolo step e side_dist iniziale
        if (ray_dir_x < 0) {
            step_x = -1;
            side_dist_x = (ray_x - map_x) * delta_dist_x;
        } else {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - ray_x) * delta_dist_x;
        }
        if (ray_dir_y < 0) {
            step_y = -1;
            side_dist_y = (ray_y - map_y) * delta_dist_y;
        } else {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - ray_y) * delta_dist_y;
        }

        // Lancio del raggio
        while (hit == 0) {
            if (side_dist_x < side_dist_y) {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            } else {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            // Controllo collisione con muro o uscita dalla mappa
            if (map_x < 0 || map_x >= map->map_width || 
                map_y < 0 || map_y >= map->map_height) {
                hit = 1; // Raggio uscito dalla mappa
            } else if (map->world[map_y][map_x] == '1') {
                hit = 1; // Muro colpito
            }
        }

        // 4. Calcolo distanza (senza fisheye)
        double perp_wall_dist;
        if (side == 0) {
            perp_wall_dist = (map_x - ray_x + (1 - step_x) / 2) / ray_dir_x;
        } else {
            perp_wall_dist = (map_y - ray_y + (1 - step_y) / 2) / ray_dir_y;
        }

        // 5. Altezza della linea da disegnare
        int line_height = (int)(game->screen_h / perp_wall_dist);
        int draw_start = -line_height / 2 + game->screen_h / 2;
        if (draw_start < 0) draw_start = 0;
        int draw_end = line_height / 2 + game->screen_h / 2;
        if (draw_end >= game->screen_h) draw_end = game->screen_h - 1;

        // 6. Colore in base al lato del muro
        int color = (side == 1) ? 0x808080 : 0xFFFFFF; // Grigio per y-side, bianco per x-side

        // 7. Disegna la linea verticale
        for (int y = draw_start; y < draw_end; y++) {
            my_pixel_put(x, y, game, color);
        }
    }
}