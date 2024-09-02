/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 08:11:00 by moel-fat          #+#    #+#             */
/*   Updated: 2024/09/02 11:57:29 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include <stdbool.h>
# include "../libft/libft.h"
# include <stdlib.h>
# include <string.h>
#include <float.h>

# define HEIGHT  			900 
# define WIDTH  			1600 
# define CENTER_CIRCLE 		110
# define RADIUS 			100
# define RADIUS_X2			(RADIUS * RADIUS)
# define MINIMAP_WIDTH 		210
# define MINIMAP_HEIGHT 	210
# define PLAYER_SIZE     	10
# define PLAYER_R			(PLAYER_SIZE / 2)
# define PLAYER_PIX_CENTER	110
# define PLAYER_SPEED		12

//colors
# define BLACK  0x000000FF
# define WHITE  0xFFFFFFFF
# define RED    0xFF0000FF
# define GRAY   0x36454FFF
# define Maroon 0xFF800000
# define Gold	0xFFEE82EE

//Keys
# define KEY_PRESS		2
#define TILE_SIZE       32
#define MAP_NUM_ROWS    14
#define MAP_NUM_COLS    32
#define PI              3.14159265
#define FOV_ANGLE       (60 * (PI / 180))
#define SCALE_FACTOR    0.2

typedef struct s_data
{
	char			*data;
	struct s_data	*next;
} t_data;

typedef struct s_render_vars
{
	int mapX;
	int	mapY;
    int xOffset;
	int	yOffset;
}	t_render_vars;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}t_color;

typedef struct s_ray_cast
{
	double yinter;
    double xinter;
    double xstep;
    double ystep;
} t_ray_cast;

typedef struct s_map
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	t_color floor;
	t_color ceiling;
	char	**map;
	char 	**v_map;
	int		height;
	int		width;
	int 	player_dir;
	int		player_x;
	int		player_y;
	int		map_fd;
	t_data	*data;
}t_map;

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
    bool    was_hit_horz;
	double	wall_hit_x_ver;
	double	wall_hit_y_ver;
} t_ray;

typedef struct  s_player
{
    double  	x;
    double  	y;
    int			width;
    int			height;
    int     	turn_direction;
    int     	walk_direction;
	int     	strafe_direction;
    double  	rotation_angle;
    double  	walk_speed;
    double  	turn_speed;
} t_player;

typedef struct s_window
{
	mlx_t        	*mlx_con;
	void        	*mlx_window;
	mlx_image_t     *img;
    t_map			*map;
	char			**my_map;
	char        	*title;
	int				width;
	int				height;
	uint32_t		floor_color;
	uint32_t		ceiling_color;
	mlx_texture_t	**texture;
    t_player    	player;
    t_ray       	ray_list[WIDTH + 1];
}	t_window;

enum e_direction
{
	NORTH,
	SOUTH,
	EAST,
	WEST
};

//initialization
void		init_window(t_window *window);
void		init_player(t_player *player, t_map *map);
void		listen_events(t_window *window);
void		init_texture(t_window *window);

//render
void    	render(t_window *window);

//events
void		update_player(t_window *window);	

//raycasting && ray_cast_utils
void		rays_casting(t_window *window);
void		init_horz_cast(t_ray_cast *ray_cast, t_window *window, t_ray *ray);
void		init_vert_cast(t_ray_cast *ray_var, t_window *window, t_ray *ray);
void		dda_algo(int X1, int Y1, double X, t_window *window);
int			get_step(double dx, double dy);
double		normalize_angle(double angle);

//draw_3d
void		render_walls(t_window *window);

//utils
double		get_wall_height(t_window *window, int i);
double		calc_distance(double X0, double Y0, double X, double Y);
uint32_t	convert_color(t_color *color);

//parsing
void		map_init(t_map *map);
void		check_read_map(char *filename, t_map *map);
int			ft_lstsizemap(t_data *lst);
t_data		*ft_lstlastmap(t_data *lst);
t_data		*ft_lstnewmap(char *data);
void		ft_lstadd_backmap(t_data **lst, t_data *new);
void		ft_error(t_map *map, int flag);
void		*safe_malloc(size_t size);
#endif