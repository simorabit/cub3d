#include "../includes/Cub3d.h"

bool check_hits(t_window *window, int x_new, int y_new)
{
    return ((window->map->v_map[(int)y_new / TILE_SIZE][(int)x_new / TILE_SIZE] == '1' || \
        window->map->v_map[(int)(y_new / TILE_SIZE)][(int)x_new / TILE_SIZE] == 'D'));
}

bool ray_protection(t_ray_cast ray_var, t_window *window)
{
    return (ray_var.xinter >= 0 && ray_var.xinter <= window->width && \
        ray_var.yinter >= 0 && ray_var.yinter <= window->height);
}
