/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 08:18:00 by moel-fat          #+#    #+#             */
/*   Updated: 2024/09/22 11:16:16 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	close_handler(t_window *window)
{
	mlx_delete_image(window->mlx_con, window->img);
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

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_window	*window;

	window = (t_window *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		close_handler(window);
	else if (keydata.key == MLX_KEY_W)
		player_direction(keydata, &window->player.walk_direction, 1);
	else if (keydata.key == MLX_KEY_S)
		player_direction(keydata, &window->player.walk_direction, -1);
	else if (keydata.key == MLX_KEY_A)
		player_direction(keydata, &window->player.strafe_direction, -1);
	else if (keydata.key == MLX_KEY_D)
		player_direction(keydata, &window->player.strafe_direction, 1);
	else if (keydata.key == MLX_KEY_RIGHT)
		player_direction(keydata, &window->player.turn_direction, 1);
	else if (keydata.key == MLX_KEY_LEFT)
		player_direction(keydata, &window->player.turn_direction, -1);
}
