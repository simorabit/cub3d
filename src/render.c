/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 08:18:28 by moel-fat          #+#    #+#             */
/*   Updated: 2024/08/22 13:30:21 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/Cub3d.h"

void draw_all_in_black(t_window *window)
{
    int x;
    int y;

    y = 0;

    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            if (y < HEIGHT / 2)
                mlx_put_pixel(window->img, x, y, window->floor_color);
            else
                mlx_put_pixel(window->img, x, y, window->ceiling_color);//TODO change red to ceiling color and black to floor color
            // mlx_put_pixel(window->img, x, y, RED); //TODO split the screen in half for floor and ceiling collors 
            x++;
        }
        y++;
    }
}


void draw_player(t_window *window)
{
    int x;
    int y;

    y = window->player.y;
    while (y < window->player.y + PLAYER_SIZE)
    {
        x = window->player.x;
        while (x < window->player.x + PLAYER_SIZE)
        {
            mlx_put_pixel(window->img, SCALE_FACTOR * x, SCALE_FACTOR * y, RED);
            x++;
        }
        y++;
    }
}

void draw_map(int x, int y, t_window *window)
{
    int map_x = x / TILE_SIZE;
    int map_y = y / TILE_SIZE;

    if (window->map->v_map[map_y][map_x] == '1')
        mlx_put_pixel(window->img, x * SCALE_FACTOR, SCALE_FACTOR * y, Gold);
    else
        mlx_put_pixel(window->img, SCALE_FACTOR * x, SCALE_FACTOR * y, BLACK);
}

void render(t_window *window)
{
    int x;
    int y;

    y = 0;
    draw_all_in_black(window); //TODO chnage name to match draw floor and ceiling

    while (y < window->height)
    {
        x = 0;
        while (x < window->width)
        {  
            draw_map(x, y, window);
            x++;
        }
        y++;
    }
    draw_player(window);
    rays_casting(window);
    render_walls(window);
}
