/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 08:17:51 by moel-fat          #+#    #+#             */
/*   Updated: 2024/08/28 11:24:27 by moel-fat         ###   ########.fr       */
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
    return ((uint32_t)r << 24) | ((uint32_t)g << 16) | ((uint32_t)b << 8) | (uint32_t)a;
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
    return color;
}



void render_walls(t_window *window)
{
    int i;
    double wall_top_pixel;
    double wall_bottom_pixel;
    double wall_strip_height;
    int y;

    i = 0;
    while (i < WIDTH)
    {
        double correct_distance = window->ray_list[i].distance *
            (cos(window->ray_list[i].angle - window->player.rotation_angle));
        window->ray_list[i].distance = correct_distance;
        wall_strip_height = get_wall_height(window, i);
        wall_top_pixel = (HEIGHT / 2) - (wall_strip_height / 2);
        if (wall_top_pixel < 0)
            wall_top_pixel = 0;
        wall_bottom_pixel = (HEIGHT / 2) + (wall_strip_height / 2);
        if (wall_bottom_pixel >= HEIGHT)
            wall_bottom_pixel = HEIGHT - 1;
        if (wall_strip_height > HEIGHT)
            wall_top_pixel -= (wall_strip_height - HEIGHT) / 2;
        y = wall_top_pixel;

        int direction = window->ray_list[i].was_hit_horz ? (window->ray_list[i].is_facing_up ? NORTH : SOUTH) 
                                                         : (window->ray_list[i].is_facing_left ? WEST : EAST);

        double init_x = window->ray_list[i].was_hit_horz ? 
                        (int)window->ray_list[i].wall_hit_x % TILE_SIZE : 
                        (int)window->ray_list[i].wall_hit_y % TILE_SIZE;

        uint32_t texture_x = init_x * (window->texture[direction]->width / TILE_SIZE);
        double init_y = wall_top_pixel;

        while (y <= wall_bottom_pixel)
        {
            if (i >= 0 && i < WIDTH && y >= 0 && y < HEIGHT)
            {
                uint32_t texture_y = (y - init_y) * 
                                     (window->texture[direction]->height / wall_strip_height);

                mlx_put_pixel(window->img, round(i), round(y),
                    get_pixel_color(window->texture[direction], texture_x, texture_y));
            }
            y++;
        }
        i++;
    }
}
