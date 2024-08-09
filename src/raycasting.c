/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 08:18:19 by moel-fat          #+#    #+#             */
/*   Updated: 2024/08/09 08:18:20 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/Cub3d.h"

void DDA(int X1, int Y1, t_window *window)
{
    int dx = X1 - (window->player.x + PLAYER_SIZE / 2);
    int dy = Y1 - (window->player.y + PLAYER_SIZE / 2);
    int i = 0;

    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float Xinc = dx / (float)steps;
    float Yinc = dy / (float)steps;

    float X = (window->player.x + PLAYER_SIZE / 2);
    float Y = (window->player.y + PLAYER_SIZE / 2);
    while (i <= steps)
    {
        mlx_put_pixel(window->img, round(SCALE_FACTOR * X), round(SCALE_FACTOR * Y), 0xffff00ff);
        X += Xinc; // increment in x at each step
        Y += Yinc; // increment in y at each step
        i++;
    }
}

void init_ray(t_ray *ray)
{
    ray->wall_hit_x = 0;
    ray->wall_hit_y = 0;
    if (ray->angle > 0 && ray->angle < PI)
        ray->is_facing_down = true;
    else
        ray->is_facing_down = false;
    ray->is_facing_up = !ray->is_facing_down;
    if (ray->angle < 0.5 * PI || ray->angle > 1.5 * PI)
        ray->is_facing_right = true;
    else
        ray->is_facing_right = false;
    ray->is_facing_left = !ray->is_facing_right;
    ray->distance = 0;
}

float normalize_angle(float angle)
{
    angle = fmod(angle, 2 * PI);
    if (angle < 0)
        angle = (2 * PI) + angle;
    return angle;
}

float distance_between_points(float X0, float Y0, float X, float Y)
{
    return sqrt((X - X0) * (X - X0) + (Y - Y0) * (Y - Y0));
}

void init_horz_cast(float *xstep, float *ystep, float *yintercept, t_ray *ray)
{
    *ystep = TILE_SIZE;
    *ystep *= ray->is_facing_up ? -1 : 1;
    *xstep = TILE_SIZE / tan(ray->angle);
    *xstep *= (ray->is_facing_left && *xstep > 0) ? -1 : 1;
    *xstep *= (ray->is_facing_right && *xstep < 0) ? -1 : 1;
    if (ray->is_facing_up)
        (*yintercept)--;
}

void init_vert_cast(float *xstep, float *ystep, float *xintercept, t_ray *ray)
{
    *xstep = TILE_SIZE;
    *xstep *= ray->is_facing_left ? -1 : 1;
    *ystep = TILE_SIZE * tan(ray->angle);
    *ystep *= (ray->is_facing_up && *ystep > 0) ? -1 : 1;
    *ystep *= (ray->is_facing_down && *ystep < 0) ? -1 : 1;
    if (ray->is_facing_left)
        (*xintercept)--;
}

bool horizontal_casting(t_ray *ray, t_window *window)
{
    float yintercept;
    float xintercept;
    float xstep;
    float ystep;

    yintercept = floor(window->player.y / TILE_SIZE) * TILE_SIZE;
    yintercept += ray->is_facing_down ? TILE_SIZE : 0;
    xintercept = window->player.x + (yintercept - window->player.y) / tan(ray->angle);
    init_horz_cast(&xstep, &ystep, &yintercept, ray);
    while (xintercept >= 0 && xintercept <= WIDTH && yintercept >= 0 && yintercept <= HEIGHT)
    {
        if (window->map[(int)yintercept / TILE_SIZE][(int)xintercept / TILE_SIZE] == '1')
        {
            ray->wall_hit_x = xintercept;
            ray->wall_hit_y = yintercept;
            return (true);
        }
        else
        {
            xintercept += xstep;
            yintercept += ystep;
        }
    }
    return (false);
}

bool verical_casting(t_ray *ray, t_window *window)
{
    float xintercept;
    float yintercept;
    float ystep;
    float xstep;

    xintercept = floor(window->player.x / TILE_SIZE) * TILE_SIZE;
    xintercept += ray->is_facing_right ? TILE_SIZE : 0;
    yintercept = window->player.y + (xintercept - window->player.x) * tan(ray->angle);
    init_vert_cast(&xstep, &ystep, &xintercept, ray);
    while (xintercept >= 0 && xintercept <= WIDTH && yintercept >= 0 && yintercept <= HEIGHT)
    {
        if (window->map[(int)yintercept / TILE_SIZE][(int)xintercept / TILE_SIZE] == '1')
        {
            ray->wall_hit_x_ver = xintercept;
            ray->wall_hit_y_ver = yintercept;
            return (true);
        }
        else
        {
            xintercept += xstep;
            yintercept += ystep;
        }
    }
    return (false);
}

void ray_casting(t_ray *ray, t_window *window)
{
    bool findHorizontalwall;
    bool findVerticalWallHit;
    float horz_distance;
    float vert_distance;

    init_ray(ray);
    findHorizontalwall = horizontal_casting(ray, window);
    findVerticalWallHit = verical_casting(ray, window);
    horz_distance = (findHorizontalwall) ? \
        distance_between_points(window->player.x, window->player.y, ray->wall_hit_x, ray->wall_hit_y) : INT_MAX;
    vert_distance = (findVerticalWallHit) ? \
        distance_between_points(window->player.x, window->player.y,ray->wall_hit_x_ver, ray->wall_hit_y_ver): INT_MAX;
    ray->wall_hit_x = (horz_distance < vert_distance) ? ray->wall_hit_x : ray->wall_hit_x_ver;
    ray->wall_hit_y = (horz_distance < vert_distance) ? ray->wall_hit_y : ray->wall_hit_y_ver;
    ray->distance = (horz_distance < vert_distance) ? horz_distance : vert_distance;
    ray->was_hit_vertical = (vert_distance > horz_distance);
    DDA(ray->wall_hit_x,
        ray->wall_hit_y,
        window);
}

void rays_casting(t_window *window)
{
    float   angle;
    int     i;

    i = 0;
    angle = window->player.rotation_angle - (FOV_ANGLE / 2); // -30
    while (i <= WIDTH) // 30
    {
        window->ray_list[i].angle = normalize_angle(angle);
        ray_casting(&window->ray_list[i], window);
        i++;
        angle += FOV_ANGLE / WIDTH;
    }
}
