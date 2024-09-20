/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:27:05 by mal-mora          #+#    #+#             */
/*   Updated: 2024/09/19 11:33:52 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

bool	check_hits(t_window *window, int x_new, int y_new, int is_hits)
{
	if (is_hits)
		return ((window->map->v_map[(int)y_new / TILE_SIZE][(int)x_new / \
			TILE_SIZE] == '1' || window->map->v_map[(int)(y_new / \
				TILE_SIZE)][(int)x_new / TILE_SIZE] == 'D'));
	else if (!is_hits)
		return ((window->map->v_map[(int)y_new / TILE_SIZE][(int)(x_new) / \
			TILE_SIZE] != '1') && (window->map->v_map[(int)(y_new) / \
				TILE_SIZE][(int)(x_new) / TILE_SIZE] != 'D'));
	return (false);
}

bool	ray_protection(t_ray_cast ray_var, t_window *window)
{
	return (ray_var.xinter >= 0 && ray_var.xinter <= window->width && \
		ray_var.yinter >= 0 && ray_var.yinter <= window->height);
}
