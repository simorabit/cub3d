/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 08:18:36 by moel-fat          #+#    #+#             */
/*   Updated: 2024/09/05 11:03:44 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

double get_wall_height(t_window *window, int i)
{
    double distance_proj_plane;
    double wall_strip_height;

    distance_proj_plane = (WIDTH / 2) / tan(FOV_ANGLE / 2);
    if (window->ray_list[i].distance == 0)
        window->ray_list[i].distance = 1;
    wall_strip_height = (TILE_SIZE / window->ray_list[i].distance) * distance_proj_plane;
    return (wall_strip_height);
}

uint32_t convert_color(t_color *color)
{
    return ((uint32_t)color->r << 24 | (uint32_t)color->g << 16 | (uint32_t)color->b << 8 | 255);
}
