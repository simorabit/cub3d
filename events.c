
#include "cub3d.h"
// void update_player(t_player *player)
// {
// 	int move_step;

//     player->rotation_angle = player->turn_direction * player->turn_speed;
//     move_step =  player->walk_direction * player->walk_speed;
//    	player->x += cos(player->rotation_angle) * move_step;
//     player->y += sin(player->rotation_angle) * move_step;

// }

// static int	key_handler(int keycode, t_window *window)
// {
// 	if (keycode == KEY_ESC)
// 		close_handler(window);
// 	if (keycode == KEY_UP)
// 		window->player.walk_direction = 1;
// 	else if (keycode == KEY_DOWN)
// 		window->player.walk_direction = -1;
// 	else if (keycode == KEY_RIGHT)
// 		window->player.turn_direction = 1;
// 	else if (keycode == KEY_LEFT)
// 		window->player.turn_direction = -1;
//     update_player(&window->player);
//     render(window);
// 	return (0);
// }
// Handle key press for moving up

int	close_handler(t_window *window)
{
	mlx_destroy_image(window->mlx_con, \
			window->img.img);
	mlx_destroy_window(window->mlx_con, window->mlx_window);
	exit(EXIT_SUCCESS);
	return (0);
}
static int	key_handler(int keycode, t_window *window)
{
	double new_x;
	double new_y;

	if (keycode == KEY_ESC)
		close_handler(window);
	if (keycode == KEY_UP)
	{
		new_x = window->player.x + (cos(window->player.rotation_angle) * 30);
		new_y =	window->player.y + (sin(window->player.rotation_angle) * 30);
		if((window->map[((int)new_y + PLAYER_SIZE) / TILE_SIZE][((int)new_x + PLAYER_SIZE) / TILE_SIZE] != '1'
			&& (window->map[((int)new_y) / TILE_SIZE][((int)new_x + PLAYER_SIZE) / TILE_SIZE] != '1')
			&& (window->map[((int)new_y + PLAYER_SIZE) / TILE_SIZE][((int)new_x) / TILE_SIZE] != '1'))
			&& (window->map[((int)new_y) / TILE_SIZE][((int)new_x) / TILE_SIZE] != '1'))
		{
			window->player.y = new_y;
			window->player.x = new_x;
		}
	}
	else if (keycode == KEY_DOWN)
	{
		new_x = window->player.x - (cos(window->player.rotation_angle) * 30);
		new_y =	window->player.y - (sin(window->player.rotation_angle) * 30);
		if((window->map[((int)new_y + PLAYER_SIZE) / TILE_SIZE][((int)new_x + PLAYER_SIZE) / TILE_SIZE] != '1'
			&& (window->map[((int)new_y) / TILE_SIZE][((int)new_x + PLAYER_SIZE) / TILE_SIZE] != '1')
			&& (window->map[((int)new_y + PLAYER_SIZE) / TILE_SIZE][((int)new_x) / TILE_SIZE] != '1'))
			&& (window->map[((int)new_y) / TILE_SIZE][((int)new_x) / TILE_SIZE] != '1'))
		{
			window->player.y = new_y;
			window->player.x = new_x;
		}
	}
	else if (keycode == KEY_RIGHT)
		window->player.rotation_angle += 1 * window->player.turn_speed;
	else if (keycode == KEY_LEFT)
		window->player.rotation_angle -= 1 * window->player.turn_speed;
    render(window);
	return (0);
}


void listen_events(t_window *window)
{
    mlx_hook(window->mlx_window, KEY_PRESS, 0, key_handler, window);
}
