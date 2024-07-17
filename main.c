#include "cub3d.h"

static void put_pixel(t_image *img, int x, int y, int color)
{
    int offset;

    offset = (y * img->line_length) + (x * (img->bits_per_pixel / 8));
    *(unsigned int *)(img->addr + offset) = color;
}

void draw_map(int x, int y, t_window *window)
{
    const int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1},
        {1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1},
        {1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1},
        {1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
    int map_x = x / TILE_SIZE;
    int map_y = y / TILE_SIZE;
    int color;

    if (map[map_y][map_x] == 1)
        color = 0xFFFFFF; // White for walls
    else
        color = 0x000000; // Black for empty space
    put_pixel(&window->img, x, y, color);
}

void render(t_window *window)
{
    int x;
    int y;

    y = 0;
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
    mlx_put_image_to_window(window->mlx_con,
                            window->mlx_window,
                            window->img.img,
                            0, 0);
}

void init_player(t_player *player)
{
    player->x = WIDTH / 2;
    player->y = HIGHT / 2;
    player->width = 10;
    player->hight = 10;
    player->walk_direction = 0;
    player->turn_direction = 0;
    player->rotation_angle = PI / 2;
    player->walk_speed = 10;
    player->turn_speed = 45 * (PI / 180);
}
void draw_line(t_window *window, int x_start, int y_start, int length, int color)
{
    int x = x_start;
    int y = y_start;

    for (int i = 0; i < length; i++) {
        put_pixel(&window->img, x, y, color);
        y--; // move right
    }
}

int  render_player(t_player *player, t_window *window)
{
    int x;
    int y;

    y = player->y;
    while (y < (player->hight + player->y))
    {
        x = player->x;
        while (x < (player->width + player->x))
        {
            put_pixel(&window->img, x, y, RED);
            x++;
        }
        y++;
    }
    draw_line(window, player->x + (player->width / 2), player->y, 50 , RED);
    mlx_put_image_to_window(window->mlx_con,
                            window->mlx_window,
                            window->img.img,
                            0, 0);
    return 1;
}
static void display_window(t_window *window)
{
    t_player player;

    init_window(window);
    render(window);
    init_player(&player);

    listen_events(window, &player);
    mlx_loop(window->mlx_con);
    // mlx_loop_hook(window->mlx_window, render_player, &player);
}

int main(int argc, char *argv[])
{
    t_window window;

    (void)argc;
    (void)argv;
    display_window(&window);

    return 0;
}
