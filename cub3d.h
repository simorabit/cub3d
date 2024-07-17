# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <mlx.h>

# define HIGHT  832
# define WIDTH  1280
# define BLACK  0x000000
# define White  0xffffff
# define RED    0xFF0000

# define KEY_ESC	53
# define ZOOM_OUT	4
# define ZOOM_IN	5
# define KEY_UP	69
# define KEY_DOWN	78
# define KEY_CLOSE	17
# define KEY_LEFT   113  // Left arrow key
# define KEY_RIGHT  114  // Right arrow key

# define KEY_PRESS			2

#define TILE_SIZE  64
#define MAP_NUM_ROWS 13
#define MAP_NUM_COLS 20
#define PI 3.14159265
#define FOV_ANGLE (60 * (PI / 180))
extern const int map[MAP_NUM_ROWS][MAP_NUM_COLS];

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_window
{
	void	*mlx_con;
	void	*mlx_window;
	t_image	img;
	char	*title;
}	t_window;

typedef struct  s_player
{
    double  x;
    double  y;
    double  width;
    double  hight;
    int     turn_direction;
    int     walk_direction;
    double  rotation_angle;
    double  walk_speed;
    double  turn_speed;
} t_player;

//functions

void	init_window(t_window *window);
void	listen_events(t_window *window, t_player *player);
void    render(t_window *window);
int     render_player(t_player *player, t_window *window);