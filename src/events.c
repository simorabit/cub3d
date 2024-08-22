/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 08:18:00 by moel-fat          #+#    #+#             */
/*   Updated: 2024/08/22 14:48:09 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/Cub3d.h"

// void update_player(t_window *window)
// {
// 	int move_step;
// 	double new_x;
// 	double new_y;

// 	window->player.rotation_angle += window->player.turn_direction * window->player.turn_speed;
// 	move_step = window->player.walk_direction * window->player.walk_speed;
// 	new_x = window->player.x + (cos(window->player.rotation_angle) * move_step);
// 	new_y = window->player.y + (sin(window->player.rotation_angle) * move_step);
// 	if ((window->map->v_map[((int)new_y + PLAYER_SIZE) / TILE_SIZE][((int)new_x + PLAYER_SIZE) / TILE_SIZE] != '1'\
// 	  && (window->map->v_map[((int)new_y) / TILE_SIZE][((int)new_x + PLAYER_SIZE) / TILE_SIZE] != '1') && \
// 	  	(window->map->v_map[((int)new_y + PLAYER_SIZE) / TILE_SIZE][((int)new_x) / TILE_SIZE] != '1')) && \
// 			 (window->map->v_map[((int)new_y) / TILE_SIZE][((int)new_x) / TILE_SIZE] != '1'))
// 	{
// 		window->player.y = new_y;
// 		window->player.x = new_x;
// 	}
// }


void update_player(t_window *window)
{
    int move_step;
    int strafe_step;
    double new_x;
    double new_y;

    window->player.rotation_angle += window->player.turn_direction * window->player.turn_speed;
    
    // Calculate the forward/backward movement
    move_step = window->player.walk_direction * window->player.walk_speed;
    // Calculate the strafing movement
    strafe_step = window->player.strafe_direction * window->player.walk_speed;

    // Calculate the new position with strafing
    new_x = window->player.x + (cos(window->player.rotation_angle) * move_step) - (sin(window->player.rotation_angle) * strafe_step);
    new_y = window->player.y + (sin(window->player.rotation_angle) * move_step) + (cos(window->player.rotation_angle) * strafe_step);

    // Check for collisions before updating the player's position
    if ((window->map->v_map[((int)new_y + PLAYER_SIZE) / TILE_SIZE][((int)new_x + PLAYER_SIZE) / TILE_SIZE] != '1' \
        && (window->map->v_map[((int)new_y) / TILE_SIZE][((int)new_x + PLAYER_SIZE) / TILE_SIZE] != '1') && \
        (window->map->v_map[((int)new_y + PLAYER_SIZE) / TILE_SIZE][((int)new_x) / TILE_SIZE] != '1')) && \
        (window->map->v_map[((int)new_y) / TILE_SIZE][((int)new_x) / TILE_SIZE] != '1'))
    {
        window->player.y = new_y;
        window->player.x = new_x;
    }
}


int	close_handler(t_window *window)
{
	mlx_delete_image(window->mlx_con, \
			window->img);
	// mlx_destroy_window(window->mlx_con, window->mlx_window);
	exit(EXIT_SUCCESS);
	return (0);
}

void	player_direction(mlx_key_data_t keydata, int *key, int value)
{
	if (keydata.action == MLX_RELEASE)
		*key = 0;
	else
		*key = value;
}

// void my_keyhook(mlx_key_data_t keydata, void* param)
// {
// 	t_window *window = (t_window *)param;
// 	//TODO need to updated keys left right arrows just for changing the angle W A S D for moving
// 	if (keydata.key == MLX_KEY_ESCAPE)
// 		close_handler(window);
// 	if (keydata.key == MLX_KEY_W)
// 		player_direction(keydata, &window->player.walk_direction, 1);
// 	// else if (keydata.key == MLX_KEY_A)
// 	// 
// 	// else if (keydata.key == MLX_KEY_D)
// 	// 
// 	else if (keydata.key == MLX_KEY_S)
// 		player_direction(keydata, &window->player.walk_direction, -1);
// 	else if (keydata.key == MLX_KEY_RIGHT)
// 		player_direction(keydata, &window->player.turn_direction, 1);
// 	else if (keydata.key == MLX_KEY_LEFT)
// 		player_direction(keydata, &window->player.turn_direction, -1);
// 	// update_player(window); //TODO moved to loop_func in main.c for faster response
// }


void my_keyhook(mlx_key_data_t keydata, void* param)
{
    t_window *window = (t_window *)param;

    if (keydata.key == MLX_KEY_ESCAPE)
        close_handler(window);
    if (keydata.key == MLX_KEY_W)
        player_direction(keydata, &window->player.walk_direction, 1);  // Move forward
    else if (keydata.key == MLX_KEY_S)
        player_direction(keydata, &window->player.walk_direction, -1); // Move backward
    else if (keydata.key == MLX_KEY_A)
        player_direction(keydata, &window->player.strafe_direction, -1); // Strafe left
    else if (keydata.key == MLX_KEY_D)
        player_direction(keydata, &window->player.strafe_direction, 1);  // Strafe right
    else if (keydata.key == MLX_KEY_RIGHT)
        player_direction(keydata, &window->player.turn_direction, 1);  // Turn right
    else if (keydata.key == MLX_KEY_LEFT)
        player_direction(keydata, &window->player.turn_direction, -1); // Turn left

    // Reset directions when keys are released
    if (keydata.action == MLX_RELEASE)
    {
        if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_S)
            window->player.walk_direction = 0;
        if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_D)
            window->player.strafe_direction = 0;
        if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_LEFT)
            window->player.turn_direction = 0;
    }
}


void listen_events(t_window *window)
{
    mlx_key_hook(window->mlx_con, my_keyhook, window);
}
