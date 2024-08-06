#include "cub3d.h"

void draw_all_in_black(t_window *window)
{
    int x;
    int y;

    y = 0;

    while (y < HIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            put_pixel(&window->img, x, y, BLACK);
            x++;
        }
        y++;
    }
}

void draw_line(t_window *window, int x_start, int y_start, int length, int color)
{
    int x = x_start + TILE_SIZE / 2;
    int y = y_start + TILE_SIZE / 2;
    int i;

    i = 0;
    while (i < length)
    {
        put_pixel(&window->img, SCALE_FACTOR * x, SCALE_FACTOR * y, color);
        y--; // move right
        i++;
    }
}

void draw_player(t_window *window)
{
    int x;
    int y;

    y = window->player.y;
    while (y < window->player.y + PLAYER_SIZE)
    {
        x = window->player.x;
        while (x < window->player.x + PLAYER_SIZE)
        {
            put_pixel(&window->img, SCALE_FACTOR * x, SCALE_FACTOR * y, RED);
            x++;
        }
        y++;
    }
}

void draw_map(int x, int y, t_window *window)
{
    int map_x = x / TILE_SIZE;
    int map_y = y / TILE_SIZE;

    if ((window->map[map_y][map_x] == '1') && ((x % TILE_SIZE) && (y % TILE_SIZE)))
        put_pixel(&window->img, x * SCALE_FACTOR, SCALE_FACTOR * y, White);
    else
        put_pixel(&window->img, SCALE_FACTOR * x, SCALE_FACTOR * y, BLACK);
}

void render(t_window *window)
{
    int x;
    int y;

    y = 0;
    draw_all_in_black(window);
    while (y < HIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            draw_map(x, y, window);
            x++;
        }
        y++;
    }
    draw_player(window);
    ray_casting(window);
    render_walls(window);
    mlx_put_image_to_window(window->mlx_con,
                            window->mlx_window,
                            window->img.img,
                            0, 0);
}
