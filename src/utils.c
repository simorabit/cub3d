/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 08:18:36 by moel-fat          #+#    #+#             */
/*   Updated: 2024/08/31 11:25:57 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

double get_wall_height(t_window *window, int i)
{
    double distance_proj_plane;
    double wall_strip_height;

    distance_proj_plane = (WIDTH / 2) / tan(FOV_ANGLE / 2);
    wall_strip_height = (TILE_SIZE / window->ray_list[i].distance) * distance_proj_plane;
    return (wall_strip_height);
}

uint32_t convert_color(t_color *color)
{
    return ((uint32_t)color->r << 24 | (uint32_t)color->g << 16 | (uint32_t)color->b << 8 | 255);
}

double calc_distance(double X0, double Y0, double X, double Y)
{
    return sqrt((X - X0) * (X - X0) + (Y - Y0) * (Y - Y0));
}
