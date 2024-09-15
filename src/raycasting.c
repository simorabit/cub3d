/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 08:18:19 by moel-fat          #+#    #+#             */
/*   Updated: 2024/09/14 11:55:51 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/Cub3d.h"

bool horizontal_casting(t_ray *ray, t_window *window)
{
    t_ray_cast  ray_var;
    double      x_new;
    double      y_new;
    
    init_horz_cast(&ray_var, window, ray);
    while (ray_var.xinter >= 0 && ray_var.xinter <= window->width \
        && ray_var.yinter >= 0 && ray_var.yinter <= window->height)
    {
        if (ray->is_facing_up)
            y_new = ray_var.yinter -1;
        else
            y_new = ray_var.yinter;
        x_new = ray_var.xinter ;
        if (window->map->v_map[(int)y_new / TILE_SIZE][(int)x_new / TILE_SIZE]
            == '1')
        {
            ray->wall_hit_x = ray_var.xinter ;
            ray->wall_hit_y = ray_var.yinter;
            return (true);
        }
        else
           (1) && (ray_var.xinter += ray_var.xstep,ray_var.yinter += ray_var.ystep);
    }
    return (false);
}

bool verical_casting(t_ray *ray, t_window *window)
{
    t_ray_cast  ray_var;
    double      x_new;
    double      y_new;

    init_vert_cast(&ray_var, window, ray);
    while (ray_var.xinter >= 0 && ray_var.xinter <= window->width && \
         ray_var.yinter >= 0 && ray_var.yinter <= window->height)
    {
        if (ray->is_facing_left)
            x_new = ray_var.xinter - 1;
        else
            x_new = ray_var.xinter;
        y_new = ray_var.yinter;
        if (window->map->v_map[(int)y_new / TILE_SIZE][(int)x_new / TILE_SIZE] 
            == '1')
        {
            ray->wall_hit_x_ver = ray_var.xinter;
            ray->wall_hit_y_ver = ray_var.yinter;
            return (true);
        }
        else
            (1) && (ray_var.xinter += ray_var.xstep, 
                ray_var.yinter += ray_var.ystep);
    }
    return (false);
}

void init_ray(t_ray *ray, bool *find_hor, bool *find_ver, t_window *window)
{
    ray->wall_hit_x = 0;
    ray->wall_hit_y = 0;
    if (ray->angle > 0 && ray->angle < M_PI)
        ray->is_facing_down = true;
    else
        ray->is_facing_down = false;
    ray->is_facing_up = !ray->is_facing_down;
    if (ray->angle < 0.5 * M_PI || ray->angle > 1.5 * M_PI)
        ray->is_facing_right = true;
    else
        ray->is_facing_right = false;
    ray->is_facing_left = !ray->is_facing_right;
    ray->distance = 0;
    *find_hor = horizontal_casting(ray, window);
    *find_ver = verical_casting(ray, window);
}

void ray_cast(t_ray *ray, t_window *window)
{
    bool    find_h_wall;
    bool    find_v_Wall;
    double  horz_distance;
    double  vert_distance;

    init_ray(ray, &find_h_wall, &find_v_Wall, window);
    if (find_h_wall)
        horz_distance = calc_distance(window->player.x, \
            window->player.y, ray->wall_hit_x, ray->wall_hit_y);
    else
        horz_distance = DBL_MAX;
    if(find_v_Wall)
       vert_distance = calc_distance(window->player.x, \
        window->player.y,ray->wall_hit_x_ver, ray->wall_hit_y_ver);
    else
        vert_distance = DBL_MAX;
    if (horz_distance >= vert_distance)
        ray->wall_hit_x = ray->wall_hit_x_ver;
    if (horz_distance >= vert_distance)
        ray->wall_hit_y  = ray->wall_hit_y_ver;
    if (horz_distance <= vert_distance)
        ray->distance = horz_distance;
    else
        ray->distance = vert_distance;
    ray->was_hit_horz = (vert_distance > horz_distance);
}

void rays_casting(t_window *window)
{
    double   angle;
    int     i;

    i = 0;
    angle = window->player.rotation_angle - (FOV_ANGLE / 2); // -30
    while (i < WIDTH) // 30
    {
        window->ray_list[i].angle = normalize_angle(angle);
        ray_cast(&window->ray_list[i], window);
        // if (i == (WIDTH / 2))
        //     dda_algo(window->ray_list[i].wall_hit_x, \
        //         window->ray_list[i].wall_hit_y, \
        //         window->player.x + (PLAYER_SIZE / 2), window);
        i++;
        angle += FOV_ANGLE /(float)WIDTH;
    }
}

