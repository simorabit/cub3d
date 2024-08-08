
#include "../includes/Cub3d.h"


int get_wall_height(t_window *window, int i)
{
    int distance_proj_plane;
    int wall_strip_height;

    distance_proj_plane = (WIDTH / 2) / tan(FOV_ANGLE / 2);
    wall_strip_height = ((float)TILE_SIZE / window->ray_list[i].distance) * distance_proj_plane;
    return (wall_strip_height);
}
