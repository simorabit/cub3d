#include "cub3d.h"

void init_player(t_player *player)
{
    player->x = 1 * TILE_SIZE;
    player->y = 8 * TILE_SIZE;
    player->width = 10;
    player->hight = 10;
    player->walk_direction = 0;
    player->turn_direction = 0;
    player->rotation_angle = 0;
    player->walk_speed = 10;
    player->turn_speed = 10 * (PI / 180);
}

void	init_window(t_window *window)
{
	window->title = "CUB3D"; // Properly allocate and initialize window title
    if (!window->title)
    {
        perror("Error in allocation");
        exit(EXIT_FAILURE);
    }
	window->mlx_con = mlx_init();
	if (!window->mlx_con)
		(perror("Error in allocation"), exit(EXIT_FAILURE));
	window->mlx_window = mlx_new_window(window->mlx_con, WIDTH, \
			HIGHT, \
			window->title);
	if (!window->mlx_window)
		(perror("Error in allocation"), exit(EXIT_FAILURE));
	window->img.img = mlx_new_image(window->mlx_con, WIDTH, HIGHT);
	
	if (!window->img.img)
	{
		mlx_destroy_window(window->mlx_con, window->mlx_window);
		(perror("Error in allocation"), exit(EXIT_FAILURE));
	}
	window->img.addr = mlx_get_data_addr(window->img.img, \
		&window->img.bits_per_pixel, \
		&window->img.line_length, \
		&window->img.endian);
	if (!window->img.addr)
	{
		mlx_destroy_image(window->mlx_con, window->img.img);
		mlx_destroy_window(window->mlx_con, window->mlx_window);
		(perror("Error in allocation"), exit(EXIT_FAILURE));
	}
	window->map = NULL;
	// init_data(window);
}