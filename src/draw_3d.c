/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 08:17:51 by moel-fat          #+#    #+#             */
/*   Updated: 2024/09/03 13:21:53 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

int get_wall_direction(t_ray *ray)
{
    if (ray->was_hit_horz)
    {
        if (ray->is_facing_up)
            return (NORTH);
        else
            return (SOUTH);
    }
    else
    {
        if (ray->is_facing_left)
            return (WEST);
        else
            return (EAST);
    }
}

double get_initial_x(t_ray *ray)
{
    if (ray->was_hit_horz)
        return ((int)ray->wall_hit_x % TILE_SIZE);
    else
        return ((int)ray->wall_hit_y % TILE_SIZE);
}

void render_wall_strip(t_window *window, int i, int direction, double wall_top_pixel, double wall_bottom_pixel, double wall_strip_height)
{
    double init_x;
    uint32_t texture_x;
    uint32_t texture_y;
    double init_y;
    int y;

    init_x = get_initial_x(&window->ray_list[i]);
    texture_x = init_x * (window->texture[direction]->width / TILE_SIZE);
    init_y = wall_top_pixel;
    y = wall_top_pixel;
    while (y < wall_bottom_pixel)
    {
        if (i >= 0 && i < WIDTH && y >= 0 && y < HEIGHT)
        {
            texture_y = (uint32_t)(y - init_y) * (window->texture[direction]->height / wall_strip_height);
            mlx_put_pixel(window->img, round(i), round(y), get_pixel_color(window->texture[direction], texture_x, texture_y));
        }
        y++;
    }
}

void render_walls(t_window *window)
{
    double wall_strip_height;
    double wall_top_pixel ;
    double wall_bottom_pixel;
    int direction;
    int i = 0;

    while (i < WIDTH)
    {
        calculate_correct_distance(window, i);
        wall_strip_height = get_wall_height(window, i); // projection wall
        wall_top_pixel = calculate_wall_top_pixel(wall_strip_height);
        wall_bottom_pixel = calculate_wall_bottom_pixel(wall_strip_height);
        direction = get_wall_direction(&window->ray_list[i]);
        if (wall_strip_height > HEIGHT)
            wall_top_pixel -= (wall_strip_height - HEIGHT) / 2;
        render_wall_strip(window, i, direction, wall_top_pixel, wall_bottom_pixel, wall_strip_height);
        i++;
    }
}
