
#include "../includes/Cub3d.h"

void update_player(t_player *player)
{
	int move_step;

    player->rotation_angle += player->turn_direction * player->turn_speed;
    move_step =  player->walk_direction * player->walk_speed;
   	player->x += cos(player->rotation_angle) * move_step;
    player->y += sin(player->rotation_angle) * move_step;
}

int	close_handler(t_window *window)
{
	mlx_delete_image(window->mlx_con, \
			window->img);
	// mlx_destroy_window(window->mlx_con, window->mlx_window);
	exit(EXIT_SUCCESS);
	return (0);
}

void	player_direction(mlx_key_data_t keydata, int *key, int value)
{
	if (keydata.action == MLX_RELEASE)
		*key = 0;
	else
		*key = value;
}

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	t_window *window = (t_window *)param;

	if (keydata.key == MLX_KEY_ESCAPE)
		close_handler(window);
	if (keydata.key == MLX_KEY_UP)
		player_direction(keydata, &window->player.walk_direction, 1);
	else if (keydata.key == MLX_KEY_DOWN)
		player_direction(keydata, &window->player.walk_direction, -1);
	else if (keydata.key == MLX_KEY_RIGHT)
		player_direction(keydata, &window->player.turn_direction, 1);
	else if (keydata.key == MLX_KEY_LEFT)
		player_direction(keydata, &window->player.turn_direction, -1);
	update_player(&window->player);
}

void listen_events(t_window *window)
{
    mlx_key_hook(window->mlx_con, my_keyhook, window);
}
