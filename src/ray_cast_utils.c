/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:04:05 by mal-mora          #+#    #+#             */
/*   Updated: 2024/09/24 15:40:01 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_step(double dx, double dy)
{
	if (fabs(dx) > fabs(dy))
		return (fabs(dx));
	else
		return (fabs(dy));
}

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}

void	init_horz_cast(t_ray_cast *ray_cast, t_window *window, t_ray *ray)
{
	ray_cast->yinter = floor(window->player.y / TILE_SIZE) * TILE_SIZE;
	if (ray->is_facing_down)
		ray_cast->yinter += TILE_SIZE;
	else
		ray_cast->yinter += 0;
	ray_cast->xinter = window->player.x + \
		(ray_cast->yinter - window->player.y) / tan(ray->ray_angle);
	ray_cast->ystep = TILE_SIZE;
	if (ray->is_facing_up)
		ray_cast->ystep *= -1;
	else
		ray_cast->ystep *= 1;
	ray_cast->xstep = TILE_SIZE / tan(ray->ray_angle);
	if (ray->is_facing_left && ray_cast->xstep > 0)
		ray_cast->xstep *= -1;
	else
		ray_cast->xstep *= 1;
	if (ray->is_facing_right && ray_cast->xstep < 0)
		ray_cast->xstep *= -1;
	else
		ray_cast->xstep *= 1;
}

void	init_ray(t_ray *ray)
{
	ray->wall_hit_x = 0;
	ray->wall_hit_y = 0;
	if (ray->ray_angle > 0 && ray->ray_angle < M_PI)
		ray->is_facing_down = true;
	else
		ray->is_facing_down = false;
	ray->is_facing_up = !ray->is_facing_down;
	if (ray->ray_angle < 0.5 * M_PI || ray->ray_angle > 1.5 * M_PI)
		ray->is_facing_right = true;
	else
		ray->is_facing_right = false;
	ray->is_facing_left = !ray->is_facing_right;
	ray->distance = 0;
}

void	init_vert_cast(t_ray_cast *ray_var, t_window *window, t_ray *ray)
{
	ray_var->xinter = floor(window->player.x / TILE_SIZE) * TILE_SIZE;
	if (ray->is_facing_right)
		ray_var->xinter += TILE_SIZE;
	else
		ray_var->xinter += 0;
	ray_var->yinter = window->player.y + \
		(ray_var->xinter - window->player.x) * tan(ray->ray_angle);
	ray_var->xstep = TILE_SIZE;
	if (ray->is_facing_left)
		ray_var->xstep *= -1;
	else
		ray_var->xstep *= 1;
	ray_var->ystep = TILE_SIZE * tan(ray->ray_angle);
	if (ray->is_facing_up && ray_var->ystep > 0)
		ray_var->ystep *= -1;
	else
		ray_var->ystep *= 1;
	if (ray->is_facing_down && ray_var->ystep < 0)
		ray_var->ystep *= -1;
	else
		ray_var->ystep *= 1;
}
