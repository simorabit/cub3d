
#include "cub3d.h"

void render_walls(t_window *window)
{
    int i;
    int wall_top_pixel;
    int wall_bottom_pixel;
    int wall_strip_height;
    int y;

    i = 0;
    while (i < WIDTH)
    {
        int correct_distance = window->ray_list[i].distance * (cos(window->ray_list[i].angle - window->player.rotation_angle));
        window->ray_list[i].distance = correct_distance;
        wall_strip_height = get_wall_height(window, i);
        wall_top_pixel = (HIGHT / 2) - (wall_strip_height / 2);
        if (wall_top_pixel < 0)
            wall_top_pixel = 0;
        wall_bottom_pixel = (HIGHT / 2) + (wall_strip_height / 2);
        if (wall_bottom_pixel >= HIGHT)
            wall_bottom_pixel = HIGHT - 1;
        y = wall_top_pixel;
        while (y < wall_bottom_pixel)
        {
            if(window->ray_list[i].was_hit_vertical)
                put_pixel(&window->img, i, y, GRAY);
            else
                put_pixel(&window->img, i, y, White);
            y++;
        }
        i++;
    }
}