// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   render.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/08/09 08:18:28 by moel-fat          #+#    #+#             */
// /*   Updated: 2024/08/09 10:41:10 by mal-mora         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */


// #include "../includes/Cub3d.h"

// void draw_all_in_black(t_window *window)
// {
//     int x;
//     int y;

//     y = 0;

//     while (y < HEIGHT)
//     {
//         x = 0;
//         while (x < WIDTH)
//         {
//             mlx_put_pixel(window->img, x, y, BLACK);
//             x++;
//         }
//         y++;
//     }
// }


// void draw_player(t_window *window)
// {
//     int x;
//     int y;

//     y = window->player.y;
//     while (y < window->player.y + PLAYER_SIZE)
//     {
//         x = window->player.x;
//         while (x < window->player.x + PLAYER_SIZE)
//         {
//             mlx_put_pixel(window->img, SCALE_FACTOR * x, SCALE_FACTOR * y, RED);
//             x++;
//         }
//         y++;
//     }
// }

// void draw_map(int x, int y, t_window *window)
// {
//     int map_x = x / TILE_SIZE;
//     int map_y = y / TILE_SIZE;

//     if (window->map->v_map[map_y][map_x] == '1')
//         mlx_put_pixel(window->img, x * SCALE_FACTOR, SCALE_FACTOR * y, White);
//     else
//         mlx_put_pixel(window->img, SCALE_FACTOR * x, SCALE_FACTOR * y, BLACK);
// }

// void render(t_window *window)
// {
//     int x;
//     int y;

//     y = 0;
//     draw_all_in_black(window);
//     while (y < HEIGHT)
//     {
//         x = 0;
//         while (x < WIDTH)
//         {  
//             draw_map(x, y, window);
//             x++;
//         }
//         y++;
//     }
//     draw_player(window);
//     rays_casting(window);
//     render_walls(window);
// }


#include "../includes/Cub3d.h"

// Calculate the scale factor to fit the map within the fixed window size
float calculate_scale_factor(t_window *window)
{
    float scale_x = (float)WIDTH / (window->map->width * TILE_SIZE);
    float scale_y = (float)HEIGHT / (window->map->height * TILE_SIZE);
    return (scale_x < scale_y) ? scale_x : scale_y;
}

void draw_all_in_black(t_window *window)
{
    int x, y;

    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            mlx_put_pixel(window->img, x, y, BLACK);
            x++;
        }
        y++;
    }
}

void draw_player(t_window *window, float scale_factor)
{
    int x, y;
    int scaled_x = window->player.x * scale_factor;
    int scaled_y = window->player.y * scale_factor;
    int scaled_size = PLAYER_SIZE * scale_factor;

    y = scaled_y;
    while (y < scaled_y + scaled_size)
    {
        x = scaled_x;
        while (x < scaled_x + scaled_size)
        {
            mlx_put_pixel(window->img, x * SCALE_FACTOR, y * SCALE_FACTOR, RED);
            x++;
        }
        y++;
    }
}

void draw_map(t_window *window, float scale_factor)
{
    int x, y;
    int scaled_tile_size = TILE_SIZE * scale_factor;

    for (y = 0; y < window->map->height; y++)
    {
        for (x = 0; x < window->map->width; x++)
        {
            int screen_x = x * scaled_tile_size;
            int screen_y = y * scaled_tile_size;

            if (window->map->v_map[y][x] == '1')
            {
                for (int i = 0; i < scaled_tile_size; i++)
                {
                    for (int j = 0; j < scaled_tile_size; j++)
                    {
                        mlx_put_pixel(window->img, (screen_x + i) * SCALE_FACTOR , (screen_y + j) * SCALE_FACTOR, White);
                    }
                }
            }
        }
    }
}

void render(t_window *window)
{
    float scale_factor = calculate_scale_factor(window);

    draw_all_in_black(window);
    draw_map(window, scale_factor);
    draw_player(window, scale_factor);
    rays_casting(window); // Assuming you will adapt ray casting and wall rendering to the scale
    render_walls(window);
}
