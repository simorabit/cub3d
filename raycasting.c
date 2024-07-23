
#include "cub3d.h"

void DDA(int X0, int Y0, int X1, int Y1, t_window *window, t_ray *mray)
{
    int dx = X1 - X0;
    int dy = Y1 - Y0;

    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float Xinc = dx / (float)steps;
    float Yinc = dy / (float)steps;

    // Put pixel for each step
    float X = X0;
    float Y = Y0;
    while (1)
    {
        put_pixel(&window->img, SCALE_FACTOR * X, SCALE_FACTOR * Y, 0xffff00);
        X += Xinc; // increment in x at each step
        Y += Yinc; // increment in y at each step
        if (window->map[(int)Y / TILE_SIZE][(int)X / TILE_SIZE] == '1')
        {
            mray->distance = sqrt((X - X0) * (X - X0) + (Y - Y0) * (Y - Y0));
            break;
        }
    }
}

void ray_casting(t_window *window)
{
    double angle;
    int i;

    i = 0;
    angle = window->player.rotation_angle - FOV_ANGLE / 2; // -30

    while (i <= WIDTH) // 30
    {
        DDA((window->player.x + PLAYER_SIZE / 2), window->player.y + PLAYER_SIZE / 2,
            (window->player.x + PLAYER_SIZE / 2) + cos(angle) * 300,
            (window->player.y + PLAYER_SIZE / 2) + sin(angle) * 300,
            window, &window->ray_list[i]);
        window->ray_list[i].angle = angle;
        i++;
        angle += FOV_ANGLE / WIDTH;
    }
}