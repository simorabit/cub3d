/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:16:24 by mal-mora          #+#    #+#             */
/*   Updated: 2024/09/20 18:06:01 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

bool is_hit_wall(t_window *window, double new_x, double new_y)
{
	if (check_hits(window, new_x, new_y, 0))
		return (true);
	else
		return (false);
}

// void update_player(t_window *window)
// {
// 	int move_step;
// 	int strafe_step;
// 	double new_x;
// 	double new_y;
// 	int i;

// 	window->player.rotation_angle += (window->player.turn_direction * window->player.turn_speed);
// 	move_step = window->player.walk_direction * window->player.walk_speed;
// 	strafe_step = window->player.strafe_direction * window->player.walk_speed;
// 	new_x = window->player.x + (cos(window->player.rotation_angle) * move_step) -
// 			(sin(window->player.rotation_angle) * strafe_step);
// 	new_y = window->player.y + (sin(window->player.rotation_angle) * move_step) +
// 			(cos(window->player.rotation_angle) * strafe_step);
// 	i = 1;
// 	while (i <= abs(move_step))
// 	{
// 		window->player.rotation_angle += (window->player.turn_direction * window->player.turn_speed);
// 		double xnew_x = window->player.x + (cos(window->player.rotation_angle) * i);
// 		double ynew_y = window->player.y + (sin(window->player.rotation_angle) * i);
// 			if (is_hit_wall(window, xnew_x, ynew_y))
// 			{
// 				window->player.y = new_y;
// 				window->player.x = new_x;
// 			}
// 		i++;
// 	}
// }

void	update_player(t_window *window)
{
	int		move_step;
	int		strafe_step;
	double	new_x;
	double	new_y;

	window->player.rotation_angle += (window->player.turn_direction \
		* window->player.turn_speed);
	move_step = window->player.walk_direction * \
		window->player.walk_speed;
	strafe_step = window->player.strafe_direction \
		* window->player.walk_speed;
	new_x = window->player.x + (cos(window->player.rotation_angle) \
		* move_step) - (sin(window->player.rotation_angle) * strafe_step);
	new_y = window->player.y + (sin(window->player.rotation_angle) \
		* move_step) + (cos(window->player.rotation_angle) * strafe_step);
	if (is_hit_wall(window, new_x, new_y))
	{
		window->player.y = new_y;
		window->player.x = new_x;
	}
}
