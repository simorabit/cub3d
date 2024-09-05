/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 08:17:51 by moel-fat          #+#    #+#             */
/*   Updated: 2024/09/05 10:58:18 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

// void render_walls(t_window *window)
// {
//     int i;
//     double wall_top_pixel;
//     double wall_bottom_pixel;
//     double wall_strip_height;
//     int y;

//     i = 0;
//     while (i < WIDTH)
//     {
//         double correct_distance = window->ray_list[i].distance * \
//             (cos(window->ray_list[i].angle - window->player.rotation_angle));
//         window->ray_list[i].distance = correct_distance;
//         wall_strip_height = get_wall_height(window, i);
//         wall_top_pixel = (HEIGHT / 2) - (wall_strip_height / 2);
//         if (wall_top_pixel < 0)
//             wall_top_pixel = 0;
//         wall_bottom_pixel = (HEIGHT / 2) + (wall_strip_height / 2);
//         if (wall_bottom_pixel >= HEIGHT)
//             wall_bottom_pixel = HEIGHT - 1;
//         y = wall_top_pixel;
//         while (y < wall_bottom_pixel)
//         {
//             if(window->ray_list[i].was_hit_horz)
//                 mlx_put_pixel(window->img, round(i), round(y), GRAY);
//             else
//                 mlx_put_pixel(window->img, round(i), round(y), White);
//             y++;
//         }
//         i++;
//     }
// }


uint32_t ft_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    return (((uint32_t)r << 24) | ((uint32_t)g << 16) | ((uint32_t)b << 8) | (uint32_t)a);
}


uint32_t get_pixel_color(mlx_texture_t *texture, uint32_t x, uint32_t y)
{
    int index;
    uint32_t color;

    if (x >= 0 && x < texture->width && y >= 0 && y < texture->height)
    {
        index = (y * texture->width + x) * texture->bytes_per_pixel;
        color = ft_rgba(texture->pixels[index], texture->pixels[index + 1],
                        texture->pixels[index + 2], texture->pixels[index + 3]);
    }
    else
    {
        color = ft_rgba(0, 0, 0, 255);  // Default color (black with full opacity)
    }
    return (color);
}

void calculate_correct_distance(t_window *window, int i)
{
    window->ray_list[i].distance *= cos(window->ray_list[i].angle - window->player.rotation_angle);
}

double calculate_wall_top_pixel(double wall_strip_height)
{
    double wall_top_pixel; 

    wall_top_pixel = (HEIGHT / 2) - (wall_strip_height / 2);
    if (wall_top_pixel < 0)
        wall_top_pixel = 0;
    return (wall_top_pixel);
}

double calculate_wall_bottom_pixel(double wall_strip_height)
{
    double wall_bottom_pixel;

    wall_bottom_pixel = (HEIGHT / 2) + (wall_strip_height / 2);
    if (wall_bottom_pixel >= HEIGHT)
        wall_bottom_pixel = HEIGHT - 1;
    return (wall_bottom_pixel);
}

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
    y = (int)round(wall_top_pixel);

    while (y <= wall_bottom_pixel)
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
        wall_strip_height = get_wall_height(window, i);
        wall_top_pixel = calculate_wall_top_pixel(wall_strip_height);
        wall_bottom_pixel = calculate_wall_bottom_pixel(wall_strip_height);
        direction = get_wall_direction(&window->ray_list[i]);

        if (wall_strip_height > HEIGHT)
            wall_top_pixel -= (wall_strip_height - HEIGHT) / 2;

        render_wall_strip(window, i, direction, wall_top_pixel, wall_bottom_pixel, wall_strip_height);
        i++;
    }
}
