/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_that_booty.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-18 20:16:19 by damoncad          #+#    #+#             */
/*   Updated: 2025-02-18 20:16:19 by damoncad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    rotate_point(float *x, float *y, float center_x, float center_y, float angle)
{
    float   sin_angle;
    float   cos_angle;
    float   translated_x;
    float   translated_y;

    //trasla il punto rispetto al centro di rotazione
    translated_x = *x - center_x;
    translated_y = *y - center_y;

    //calcola seno e coseno dell'angolo
    sin_angle = sinf(angle);
    cos_angle = cosf(angle);

    //applicazione della rotazione
    *x = translated_x * cos_angle - translated_y * sin_angle + center_x;
    *y = translated_x * sin_angle + translated_y * cos_angle + center_y;
}