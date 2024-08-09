/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 08:18:19 by moel-fat          #+#    #+#             */
/*   Updated: 2024/08/09 18:33:07 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/Cub3d.h"

void DDA(int X1, int Y1, t_window *window)
{
    int dx = round(X1) - round(window->player.x + PLAYER_SIZE / 2);
    int dy = round(Y1) - round(window->player.y + PLAYER_SIZE / 2);
    int i = 0;

    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    double Xinc = dx / (double)steps;
    double Yinc = dy / (double)steps;

    double X = (window->player.x + PLAYER_SIZE / 2);
    double Y = (window->player.y + PLAYER_SIZE / 2);
    while (i <= steps)
    {
        mlx_put_pixel(window->img, SCALE_FACTOR * round(X), SCALE_FACTOR * round(Y), 0xffff00ff);
        X += Xinc; // increment in x at each step
        Y += Yinc; // increment in y at each step
        i++;
    }
}

void init_ray(t_ray *ray)
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
}

double normalize_angle(double angle)
{
    angle = fmod(angle, 2 * M_PI);
    if (angle < 0)
        angle = (2 * M_PI) + angle;
    return angle;
}

double distance_between_points(double X0, double Y0, double X, double Y)
{
    return sqrt((X - X0) * (X - X0) + (Y - Y0) * (Y - Y0));
}

void init_horz_cast(double *xstep, double *ystep, double *yintercept, t_ray *ray)
{
    *ystep = TILE_SIZE;
    (void)*yintercept;
    *ystep *= ray->is_facing_up ? -1 : 1;
    *xstep = TILE_SIZE / tan(ray->angle);
    *xstep *= (ray->is_facing_left && *xstep > 0) ? -1 : 1;
    *xstep *= (ray->is_facing_right && *xstep < 0) ? -1 : 1;
    
}

void init_vert_cast(double *xstep, double *ystep, double *xintercept, t_ray *ray)
{
    *xstep = TILE_SIZE;
    (void)*xintercept;
    *xstep *= ray->is_facing_left ? -1 : 1;
    *ystep = TILE_SIZE * tan(ray->angle);
    *ystep *= (ray->is_facing_up && *ystep > 0) ? -1 : 1;
    *ystep *= (ray->is_facing_down && *ystep < 0) ? -1 : 1;
    // if (ray->is_facing_left)
    //     (*xintercept)--;
}

bool horizontal_casting(t_ray *ray, t_window *window)
{
    double yintercept;
    double xintercept;
    double xstep;
    double ystep;

    yintercept = floor(window->player.y / TILE_SIZE) * TILE_SIZE;
    yintercept += ray->is_facing_down ? TILE_SIZE : 0;
    xintercept = window->player.x + (yintercept - window->player.y) / tan(ray->angle);
    double nextX = xintercept;
    double nextY = yintercept;
    double x_new = nextX;
    double y_new = nextY;
    init_horz_cast(&xstep, &ystep, &nextY, ray);
    while (nextX >= 0 && nextX <= window->width && nextY >= 0 && nextY <= window->height)
    {
         y_new = nextY + ((ray->is_facing_up) ? -1 : 0);
         x_new = nextX;
        if (window->map->v_map[(int)y_new / TILE_SIZE][(int)x_new / TILE_SIZE] == '1')
        {
            ray->wall_hit_x = nextX;
            ray->wall_hit_y = nextY;
            return (true);
        }
        else
        {
            nextX += xstep;
            nextY += ystep;
        }
    }
    return (false);
}

bool verical_casting(t_ray *ray, t_window *window)
{
    double xintercept;
    double yintercept;
    double ystep;
    double xstep;

    xintercept = floor(window->player.x / TILE_SIZE) * TILE_SIZE;
    xintercept += ray->is_facing_right ? TILE_SIZE : 0;
    yintercept = window->player.y + (xintercept - window->player.x) * tan(ray->angle);
    double nextX = xintercept;
    double nextY = yintercept;
    double x_new;
    double y_new;
    init_vert_cast(&xstep, &ystep, &nextX, ray);
    while (nextX >= 0 && nextX <= window->width && nextY >= 0 && nextY <= window->height)
    {
        x_new = nextX + ((ray->is_facing_left) ? -1 : 0);
        y_new = nextY;
        if (window->map->v_map[(int)y_new / TILE_SIZE][(int)x_new / TILE_SIZE] == '1')
        {
            ray->wall_hit_x_ver = nextX;
            ray->wall_hit_y_ver = nextY;
            return (true);
        }
        else
        {
            nextX += xstep;
            nextY += ystep;
        }
    }
    return (false);
}

void ray_casting(t_ray *ray, t_window *window)
{
    bool findHorizontalwall;
    bool findVerticalWallHit;
    double horz_distance;
    double vert_distance;

    init_ray(ray);
    findHorizontalwall = horizontal_casting(ray, window);
    findVerticalWallHit = verical_casting(ray, window);
    horz_distance = (findHorizontalwall) ? \
        distance_between_points(window->player.x, window->player.y, ray->wall_hit_x, ray->wall_hit_y) : INT_MAX;
    vert_distance = (findVerticalWallHit) ? \
        distance_between_points(window->player.x, window->player.y,ray->wall_hit_x_ver, ray->wall_hit_y_ver): INT_MAX;
    ray->wall_hit_x = (horz_distance <= vert_distance) ? ray->wall_hit_x : ray->wall_hit_x_ver;
    ray->wall_hit_y = (horz_distance <= vert_distance) ? ray->wall_hit_y : ray->wall_hit_y_ver;
    ray->distance = (horz_distance <= vert_distance) ? horz_distance : vert_distance;
    ray->was_hit_horz = (vert_distance > horz_distance);
    DDA(ray->wall_hit_x,
        ray->wall_hit_y,
        window);
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
        ray_casting(&window->ray_list[i], window);
        i++;
        angle += FOV_ANGLE / WIDTH;
    }
}

