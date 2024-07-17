
#include "cub3d.h"
void update_player(t_player *player)
{
	int move_step;

    player->rotation_angle = player->turn_direction * player->turn_speed;
    move_step =  player->walk_direction * player->walk_speed;
   	player->x += cos(player->rotation_angle) * move_step;
    player->y += sin(player->rotation_angle) * move_step;
}
static int	key_handler(int keycode, t_window *window, t_player *player)
{
	// if (keycode == KEY_ESC)
	// 	close_handler(player);
	(void)window;
	if (keycode == KEY_UP)
		player->walk_direction = 1;
	else if (keycode == KEY_DOWN)
		player->walk_direction = -1;
	else if (keycode == KEY_RIGHT)
		player->turn_direction = 1;
	else if (keycode == KEY_LEFT)
		player->turn_direction = -1;
	init_window(window);
    render(window);
	render_player(player, window);
    update_player(player);
	return (0);
}

// static int	key_relase(int keycode, t_window *window, t_player *player)
// {
// 	// if (keycode == KEY_ESC)
// 	// 	close_handler(player);
// 	 if (keycode == KEY_UP)
// 		player->walk_direction = 0;
// 	else if (keycode == KEY_DOWN)
// 		player->walk_direction =  0;
// 	else if (keycode == KEY_RIGHT)
// 		player->turn_direction = 0;
// 	else if (keycode == KEY_LEFT)
// 		player->turn_direction =  0;
// 	render_player(player, window);
// 	return (0);
// }

void listen_events(t_window *window, t_player *player)
{
    mlx_hook(window->mlx_window, KEY_PRESS, 0, key_handler, player);
}
