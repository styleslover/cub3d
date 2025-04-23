/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_that_booty.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 20:16:19 by damoncad          #+#    #+#             */
/*   Updated: 2025/04/23 15:53:39 by damoncad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_point(t_player *player, float center_x,
		float center_y, float angle)
{
	float	sin_angle;
	float	cos_angle;
	float	translated_x;
	float	translated_y;

	translated_x = player->rx - center_x;
	translated_y = player->ry - center_y;
	sin_angle = sinf(angle);
	cos_angle = cosf(angle);
	player->rx = translated_x * cos_angle - translated_y * sin_angle + center_x;
	player->ry = translated_x * sin_angle + translated_y * cos_angle + center_y;
}
