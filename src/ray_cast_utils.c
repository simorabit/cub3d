#include "../includes/Cub3d.h"

int get_step(double dx, double dy)
{
    if (fabs(dx) > fabs(dy))
        return fabs(dx);
    else
        return fabs(dy);
}
void dda_algo(int X1, int Y1, double X, t_window *window)
{
    double  Y;
    double  dx;
    double  dy;
    int     steps;
    
    Y = window->player.y + PLAYER_SIZE / 2;
    dx = X1 - X;
    dy = Y1 - Y;
    steps = get_step(X1 - X, Y1 - Y);
    dx /= steps;
    dy /= steps;
    while (steps-- >= 0)
    {
        mlx_put_pixel(window->img, SCALE_FACTOR * round(X), \
            SCALE_FACTOR * round(Y), 0xffff00ff);
        X += dx;
        Y += dy;
    }
}

double normalize_angle(double angle)
{
    angle = fmod(angle, 2 * M_PI);
    if (angle < 0)
        angle = (2 * M_PI) + angle;
    return angle;
}

void init_horz_cast(t_ray_cast *ray_cast, t_window *window, t_ray *ray)
{
    ray_cast->yinter = floor(window->player.y / TILE_SIZE) * TILE_SIZE;
    if (ray->is_facing_down)
        ray_cast->yinter += TILE_SIZE;
    else
        ray_cast->yinter += 0;
    ray_cast->xinter = window->player.x + \
     (ray_cast->yinter - window->player.y) / tan(ray->angle);
    ray_cast->ystep = TILE_SIZE;
    if (ray->is_facing_up)
        ray_cast->ystep *= -1;
    else
        ray_cast->ystep *= 1;
    ray_cast->xstep = TILE_SIZE / tan(ray->angle);
    if (ray->is_facing_left && ray_cast->xstep > 0)
        ray_cast->xstep *= -1;
    else
        ray_cast->xstep *= 1;
    if (ray->is_facing_right && ray_cast->xstep < 0)
        ray_cast->xstep *= -1;
    else
        ray_cast->xstep *= 1;    
}

void init_vert_cast(t_ray_cast *ray_var, t_window *window, t_ray *ray)
{
    ray_var->xinter = floor(window->player.x / TILE_SIZE) * TILE_SIZE;
    if (ray->is_facing_right)
        ray_var->xinter += TILE_SIZE;
    else
        ray_var->xinter += 0;
    ray_var->yinter = window->player.y + \
        (ray_var->xinter - window->player.x) * tan(ray->angle);
    ray_var->xstep = TILE_SIZE;
    if (ray->is_facing_left)
        ray_var->xstep *= -1;
    else
        ray_var->xstep *= 1;
    ray_var->ystep = TILE_SIZE * tan(ray->angle);
    if (ray->is_facing_up && ray_var->ystep > 0)
        ray_var->ystep *= -1;
    else
        ray_var->ystep *= 1;
    if(ray->is_facing_down && ray_var->ystep < 0)
        ray_var->ystep *= -1;
    else
        ray_var->ystep *= 1;
}
