/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 08:18:00 by moel-fat          #+#    #+#             */
/*   Updated: 2024/09/17 16:07:06 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

bool is_hit_wall(t_window *window, double new_x, double new_y)
{
    // if(window->player.y < new_y)
    //     new_y +=  PLAYER_SIZE / 2;
    // else
    //     new_y -=  PLAYER_SIZE / 2;
    // if(window->player.x < new_x)
    //     new_x +=  PLAYER_SIZE / 2;
    // else
    //     new_x -=  PLAYER_SIZE / 2;
     if ((window->map->v_map[(int)new_y / TILE_SIZE][(int)(new_x) / TILE_SIZE] != '1') &&
         (window->map->v_map[(int)(new_y + PLAYER_SIZE) / TILE_SIZE][(int)(new_x + PLAYER_SIZE) / TILE_SIZE] != 'D'))
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

    if(!is_hit_wall(window, new_x, new_y))
    {
        window->player.y = (new_y);
        window->player.x = (new_x);
    }
}

int close_handler(t_window *window)
{
    mlx_delete_image(window->mlx_con,
                     window->img);
    exit(EXIT_SUCCESS);
    return (0);
}

void player_direction(mlx_key_data_t keydata, int *key, int value)
{
    if (keydata.action == MLX_RELEASE)
        *key = 0;
    else
        *key = value;
}
// void handel_mouse(mlx_key_data_t keydata,t_window *window)
// {
//     if (keydata.action == MLX_RELEASE)
//         mlx_set_cursor_mode(window->mlx_con, MLX_MOUSE_NORMAL);
//     else
//         mlx_set_cursor_mode(window->mlx_con, MLX_MOUSE_DISABLED);
// }

void handel_release_keys(t_window *window, mlx_key_data_t keydata)
{
    if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_S)
        window->player.walk_direction = 0;
    if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_D)
        window->player.strafe_direction = 0;
    if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_LEFT)
        window->player.turn_direction = 0;
}

void my_keyhook(mlx_key_data_t keydata, void *param)
{
    t_window *window = (t_window *)param;
    
    if (keydata.key == MLX_KEY_ESCAPE)
        close_handler(window);
    if (keydata.key == MLX_KEY_W)
        player_direction(keydata, &window->player.walk_direction, 1); // Move forward
    else if (keydata.key == MLX_KEY_S)
        player_direction(keydata, &window->player.walk_direction, -1); // Move backward
    else if (keydata.key == MLX_KEY_A)
        player_direction(keydata, &window->player.strafe_direction, -1); // Strafe left
    else if (keydata.key == MLX_KEY_D)
        player_direction(keydata, &window->player.strafe_direction, 1); // Strafe right
    else if (keydata.key == MLX_KEY_RIGHT)
        player_direction(keydata, &window->player.turn_direction, 1); // Turn right
    else if (keydata.key == MLX_KEY_LEFT)
        player_direction(keydata, &window->player.turn_direction, -1); // Turn left
    if (keydata.action == MLX_RELEASE)
        handel_release_keys(window, keydata);
}

void listen_events(t_window *window)
{
    mlx_key_hook(window->mlx_con, my_keyhook, window);
}
