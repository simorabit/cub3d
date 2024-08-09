/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 08:18:00 by moel-fat          #+#    #+#             */
/*   Updated: 2024/08/09 14:36:35 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/Cub3d.h"

void update_player(t_window *window)
{
	int move_step;
	double new_x;
	double new_y;

	window->player.rotation_angle += window->player.turn_direction * window->player.turn_speed;
	move_step = window->player.walk_direction * window->player.walk_speed;
	new_x = window->player.x + (cos(window->player.rotation_angle) * move_step);
	new_y = window->player.y + (sin(window->player.rotation_angle) * move_step);
	if ((window->map->v_map[((int)new_y + PLAYER_SIZE) / TILE_SIZE][((int)new_x + PLAYER_SIZE) / TILE_SIZE] != '1'\
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

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	t_window *window = (t_window *)param;
	
	if (keydata.key == MLX_KEY_ESCAPE)
		close_handler(window);
	if (keydata.key == MLX_KEY_UP)
		player_direction(keydata, &window->player.walk_direction, 1);
	else if (keydata.key == MLX_KEY_DOWN)
		player_direction(keydata, &window->player.walk_direction, -1);
	else if (keydata.key == MLX_KEY_RIGHT)
		player_direction(keydata, &window->player.turn_direction, 1);
	else if (keydata.key == MLX_KEY_LEFT)
		player_direction(keydata, &window->player.turn_direction, -1);
	update_player(window);
}

void listen_events(t_window *window)
{
    mlx_key_hook(window->mlx_con, my_keyhook, window);
}
