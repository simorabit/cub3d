
#include "cub3d.h"

void DDA(int X0, int Y0, int X1, int Y1, t_window *window, t_ray *mray)
{
    int dx = X1 - X0;
    int dy = Y1 - Y0;
    int i = 0;

    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    (void)mray;
    float Xinc = dx / (float)steps;
    float Yinc = dy / (float)steps;

    // Put pixel for each step
    float X = X0;
    float Y = Y0;
    while (i <= steps)
    {
        put_pixel(&window->img, SCALE_FACTOR * X, SCALE_FACTOR * Y, 0xffff00);
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
    if(ray->angle <  0.5 * PI || ray->angle > 1.5 * PI)
        ray->is_facing_right = true;
    else
        ray->is_facing_right = false;
    ray->is_facing_left = !ray->is_facing_right;
    ray->distance = 0;
}

double normalize_angle(double angle)
{
    angle = fmod(angle, 2 * PI);
    if (angle < 0)
        angle = (2 * PI) + angle;
    return angle;
}

double distance_between_points(double X0, double Y0, double X, double Y)
{
    return sqrt((X - X0) * (X - X0) + (Y - Y0) * (Y - Y0));
}
void ray_casting(t_window *window)
{
    double angle;
    double xintercept;
    double yintercept;
    double xstep;
    double ystep;
    int i;

    i = 0;
    angle = window->player.rotation_angle - (FOV_ANGLE / 2); // -30
    
    while (i <= WIDTH) // 30
    {
        double wallHitx = 0;
        double wallHity = 0;
        bool find_wall = false;
        window->ray_list[i].angle = normalize_angle(angle);

        init_ray(&window->ray_list[i]);

        yintercept = floor(window->player.y / TILE_SIZE) * TILE_SIZE;
        yintercept += window->ray_list[i].is_facing_down ? TILE_SIZE : 0;

        xintercept = window->player.x + (yintercept - window->player.y) / tan(angle);
        
        ystep = TILE_SIZE;
        ystep *= window->ray_list[i].is_facing_up ? -1 : 1;

        xstep = TILE_SIZE / tan(window->ray_list[i].angle);
        xstep *= (window->ray_list[i].is_facing_left && xstep > 0) ? -1 : 1;
        xstep *= (window->ray_list[i].is_facing_right && xstep < 0) ? -1 : 1;
        
        double nextHoriz_touchx = xintercept;
        double nextHoriz_touchy = yintercept;

        if(window->ray_list[i].is_facing_up)
            nextHoriz_touchy--;

        while (nextHoriz_touchx >= 0 && nextHoriz_touchx <= WIDTH && nextHoriz_touchy >= 0 
            && nextHoriz_touchy <= HIGHT)
        {
            if(window->map[(int)nextHoriz_touchy / TILE_SIZE][(int)nextHoriz_touchx / TILE_SIZE] == '1')
            {
                find_wall = true;
                wallHitx = nextHoriz_touchx;
                wallHity = nextHoriz_touchy;
                break;
            }
            else
            {
                nextHoriz_touchx += xstep;
                nextHoriz_touchy += ystep;
            }
        }

        /////////////////////////////////vertical ///////////////////////////

        bool findVerticalWallHit = false;
        double ver_wall_hitx = 0;
        double ver_wall_hity = 0;

        xintercept = floor(window->player.x / TILE_SIZE) * TILE_SIZE;
        xintercept += window->ray_list[i].is_facing_right ? TILE_SIZE : 0;

        yintercept = window->player.y + (xintercept - window->player.x) * tan(angle);
        
        xstep = TILE_SIZE;
        xstep *= window->ray_list[i].is_facing_left ? -1 : 1;

        ystep = TILE_SIZE * tan(window->ray_list[i].angle);
        ystep *= (window->ray_list[i].is_facing_up && ystep > 0) ? -1 : 1;
        ystep *= (window->ray_list[i].is_facing_down && ystep < 0) ? -1 : 1;

        double nextVert_touchx = xintercept;
        double nextVert_touchy = yintercept;

        if(window->ray_list[i].is_facing_left)
            nextVert_touchx--;
        while (nextVert_touchx >= 0 && nextVert_touchx <= WIDTH && nextVert_touchy >= 0 
            && nextVert_touchy <= HIGHT)
        {
            if (window->map[(int)nextVert_touchy / TILE_SIZE][(int)nextVert_touchx / TILE_SIZE] == '1')
            {
                findVerticalWallHit = true;
                ver_wall_hitx = nextVert_touchx;
                ver_wall_hity = nextVert_touchy;
                break;
            }
            else
            {
                nextVert_touchx += xstep;
                nextVert_touchy += ystep;
            }
        }
        double horz_distance = (find_wall) ? distance_between_points(window->player.x, window->player.y,
            wallHitx, wallHity) : INT_MAX;
        double vert_distance = (findVerticalWallHit) ? distance_between_points(window->player.x, window->player.y,
           ver_wall_hitx, ver_wall_hity) : INT_MAX;
        window->ray_list[i].wall_hit_x  = (horz_distance < vert_distance) ?  wallHitx: ver_wall_hitx;
        window->ray_list[i].wall_hit_y = (horz_distance < vert_distance) ?  wallHity : ver_wall_hity;
        window->ray_list[i].distance = (horz_distance < vert_distance) ? horz_distance : vert_distance;
        window->ray_list[i].was_hit_vertical = (vert_distance > horz_distance);
        DDA((window->player.x + PLAYER_SIZE / 2), window->player.y + PLAYER_SIZE / 2,
             window->ray_list[i].wall_hit_x,
            window->ray_list[i].wall_hit_y,
            window, &window->ray_list[i]);
        i++;
        angle += FOV_ANGLE / WIDTH;
    }
}
