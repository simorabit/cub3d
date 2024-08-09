/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 08:11:00 by moel-fat          #+#    #+#             */
/*   Updated: 2024/08/09 09:35:08 by mal-mora         ###   ########.fr       */
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

# define PLAYER_SPEED	10
# define HEIGHT  		448 //(MAP_NUM_ROWS * TILE_SIZE)
# define WIDTH  		1024 //(MAP_NUM_COLS * TILE_SIZE)

# define BLACK  0x000000FF
# define White  0xFFFFFFFF
# define RED    0xFF0000FF
# define GRAY   0xD3D3D3FF

# define KEY_PRESS		2
#define TILE_SIZE       32
#define PLAYER_SIZE     15
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

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}t_color;

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
    float distance;
    float angle;
    float wall_stripe_height;
    float wall_hit_x;
    float wall_hit_y;
    bool    is_facing_up;
    bool    is_facing_down;
    bool    is_facing_right;
    bool    is_facing_left;
    bool    was_hit_vertical;
	float	wall_hit_x_ver;
	float	wall_hit_y_ver;
} t_ray;

typedef struct  s_player
{
    float  	x;
    float  	y;
    int		width;
    int		height;
    int     turn_direction;
    int     walk_direction;
    float  	rotation_angle;
    float  	walk_speed;
    float  	turn_speed;
} t_player;

typedef struct s_window
{
	mlx_t        *mlx_con;
	void        *mlx_window;
	mlx_image_t     *img;
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
void    rays_casting(t_window *window);
int     get_wall_height(t_window *window, int i);
void    draw_player(t_window *window);
void    render_walls(t_window *window);
void    draw_all_in_black(t_window *window);

//parsing
void map_init(t_map *map);
void check_read_map(char *filename, t_map *map);
int		ft_lstsizemap(t_data *lst);
t_data	*ft_lstlastmap(t_data *lst);
t_data	*ft_lstnewmap(char *data);
void	ft_lstadd_backmap(t_data **lst, t_data *new);
void	ft_error(t_map *map, int flag);
void	*safe_malloc(size_t size);
#endif