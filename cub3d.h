# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>

# include <mlx.h>
#include <fcntl.h>
#include <stdbool.h>
#include "get_next_line/get_next_line.h"
# define HIGHT  448 // 14 * 32
# define WIDTH  1024 // 32 * 32
# define BLACK  0x000000
# define White  0xffffff
# define RED    0xFF0000
# define GRAY   0xD3D3D3
# define KEY_ESC 			53
# define ZOOM_OUT 			4
# define ZOOM_IN 			5
# define KEY_UP 			126
# define KEY_DOWN 			125
# define KEY_LEFT 			123
# define KEY_RIGHT 			124
# define KEY_PLUS 			69
# define KEY_MINUS 			78
# define KEY_ESPACE			49
# define KEY_PRESS			2
# define KEY_CLOSE			17

# define KEY_PRESS	    2

#define TILE_SIZE       32
#define PLAYER_SIZE      15
#define MAP_NUM_ROWS    14
#define MAP_NUM_COLS    32
#define PI              3.14159265
#define FOV_ANGLE       (60 * (PI / 180))
#define SCALE_FACTOR    0.2

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct  s_ray
{
    double distance;
    double angle;
    double wall_stripe_height;
    double wall_hit_x;
    double wall_hit_y;
    bool    is_facing_up;
    bool    is_facing_down;
    bool    is_facing_right;
    bool    is_facing_left;
    bool    was_hit_vertical;

} t_ray;


typedef struct  s_player
{
    double  x;
    double  y;
    int  width;
    int  hight;
    int     turn_direction;
    int     walk_direction;
    double  rotation_angle;
    double  walk_speed;
    double  turn_speed;
} t_player;

typedef struct s_window
{
	void        *mlx_con;
	void        *mlx_window;
	t_image     img;
    char        **map;
	char        *title;
    t_player    player;
    t_ray       ray_list[WIDTH + 1];
}	t_window;



//functions

void	init_window(t_window *window);
void	listen_events(t_window *window);
void    render(t_window *window);
int	    close_handler(t_window *window);
void    init_player(t_player *player);
void    draw_all_in_black(t_window *window);
void    put_pixel(t_image *img, int x, int y, int color);
void    draw_map(int x, int y, t_window *window);
void    ray_casting(t_window *window);
int     get_wall_height(t_window *window, int i);
void    draw_player(t_window *window);
void    render_walls(t_window *window);
void    draw_all_in_black(t_window *window);
