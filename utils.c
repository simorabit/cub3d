
#include "includes/Cub3d.h"

// void put_pixel(mlx_image_t *img, int x, int y, int color)
// {
//     int offset;

//     offset = (y * img->line_length) + (x * (img->bits_per_pixel / 8));
//     *(unsigned int *)(img->addr + offset) = color;
// }

int get_wall_height(t_window *window, int i)
{
    int distance_proj_plane;
    int wall_strip_height;

    distance_proj_plane = (WIDTH / 2) / tan(FOV_ANGLE / 2);
    wall_strip_height = (TILE_SIZE / window->ray_list[i].distance) * distance_proj_plane;
    return (wall_strip_height);
}