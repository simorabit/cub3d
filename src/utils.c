/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 08:18:36 by moel-fat          #+#    #+#             */
/*   Updated: 2024/08/09 17:35:49 by mal-mora         ###   ########.fr       */
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
