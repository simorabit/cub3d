#include "includes/Cub3d.h"

void init_player(t_player *player)
{
    player->x = (12 * TILE_SIZE) + (TILE_SIZE / 2);
    player->y = (8 * TILE_SIZE) + (TILE_SIZE / 2);
    player->width = 10;
    player->height = 10;
    player->walk_direction = 0;
    player->turn_direction = 0;
    player->rotation_angle = M_PI / 2;
    player->walk_speed = 10;
    player->turn_speed = 8 * (M_PI / 180);
}

void	init_window(t_window *window)
{
	window->title = "CUB3D"; // Properly allocate and initialize window title
    if (!window->title)
    {
        perror("Error in allocation");
        exit(EXIT_FAILURE);
    }
	window->mlx_con = mlx_init(WIDTH, HEIGHT, window->title, true);
	if (!window->mlx_con)
		(perror("Error in allocation"), exit(EXIT_FAILURE));
	window->img = mlx_new_image(window->mlx_con, WIDTH, HEIGHT);
	
	if (!window->img)
	{
		mlx_delete_image(window->mlx_con, window->img);
		(perror("Error in allocation"), exit(EXIT_FAILURE));
	}
	mlx_image_to_window(window->mlx_con ,window->img, 0, 0);
}
