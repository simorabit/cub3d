/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:16:24 by mal-mora          #+#    #+#             */
/*   Updated: 2024/09/18 11:24:15 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

bool is_hit_wall(t_window *window, double new_x, double new_y)
{
    if(window->player.y < new_y)
        new_y +=  PLAYER_SIZE / 2;
    else
        new_y -=  PLAYER_SIZE / 2;
    if(window->player.x < new_x)
        new_x +=  PLAYER_SIZE / 2;
    else
        new_x -=  PLAYER_SIZE / 2;
    if ((window->map->v_map[(int)new_y / TILE_SIZE][(int)(new_x) / TILE_SIZE] != '1') &&
        (window->map->v_map[(int)(new_y) / TILE_SIZE][(int)(new_x) / TILE_SIZE] != 'D'))
        return false;
    else
        return true;
}

void update_player(t_window *window)
{
    int move_step;
    int strafe_step;
    double new_x;
    double new_y;

    window->player.rotation_angle += (window->player.turn_direction * window->player.turn_speed);
    move_step = window->player.walk_direction * window->player.walk_speed;
    strafe_step = window->player.strafe_direction * window->player.walk_speed;
    new_x = window->player.x + (cos(window->player.rotation_angle) * move_step) -
            (sin(window->player.rotation_angle) * strafe_step);
    new_y = window->player.y + (sin(window->player.rotation_angle) * move_step) +
            (cos(window->player.rotation_angle) * strafe_step);
    if (!is_hit_wall(window, new_x, new_y))
    {
        window->player.y = (new_y);
        window->player.x = (new_x);
    }
}
