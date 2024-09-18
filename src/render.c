/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 08:18:28 by moel-fat          #+#    #+#             */
/*   Updated: 2024/09/18 11:46:03 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

void    draw_floor_ceiling(t_window *window)
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
                mlx_put_pixel(window->img, x, y, window->ceiling_color);
            x++;
        }
        y++;
    }
}

void    draw_player(t_window *window)
{
    int x;
    int y;

    y = MINIMAP_WIDTH / 2;
    while (y < (MINIMAP_WIDTH / 2) + PLAYER_SIZE)
    {
        x = MINIMAP_HEIGHT / 2;
        while (x < (MINIMAP_HEIGHT / 2) + PLAYER_SIZE)
        {
            if ((x - PLAYER_PIX_CENTER) * (x - PLAYER_PIX_CENTER) + \
                (y - PLAYER_PIX_CENTER) * (y - PLAYER_PIX_CENTER) < \
                    PLAYER_R * PLAYER_R)
                        mlx_put_pixel(window->img, x, y, RED);
            x++;
        }
        y++;
    }
}

void    render_minimap(t_window *window, t_render_vars *re_vars, int x, int y)
{
    if (re_vars->mapY >= 0 && re_vars->mapX >= 0 && \
        re_vars->mapY < window->map->height && \
            re_vars->mapX < window->map->width)
    {
        if (window->map->v_map[re_vars->mapY][(re_vars->mapX)] == '1')
            mlx_put_pixel(window->img, x, y, BLACK);
        else if(window->map->v_map[re_vars->mapY][(re_vars->mapX)] == 'D')
            mlx_put_pixel(window->img, x, y, BROWN);
        else
            mlx_put_pixel(window->img, x, y, 0xFFFFFFFF);
    }
    else
        mlx_put_pixel(window->img, x, y, BLACK);
}

void render(t_window *window)
{
    int             x;
    int             y;
    t_render_vars   re_vars;

    draw_floor_ceiling(window);
    rays_casting(window);
    render_walls(window);
    re_vars.xOffset = floor(window->player.x) - CENTER_CIRCLE;
    re_vars.yOffset = floor(window->player.y) - CENTER_CIRCLE;
    y = 10;
    while (y < MINIMAP_WIDTH)
    {
        x = 10;
        while (x < MINIMAP_HEIGHT)
        {
            re_vars.mapX = (x + re_vars.xOffset) / TILE_SIZE;
            re_vars.mapY = (y + re_vars.yOffset) / TILE_SIZE;
            if ((x - CENTER_CIRCLE) * (x - CENTER_CIRCLE) + \
                (y - CENTER_CIRCLE) * (y - CENTER_CIRCLE) < RADIUS_X2)
                render_minimap(window, &re_vars, x, y);
            x++;
        }
        y++;
    }
    draw_player(window);
}
