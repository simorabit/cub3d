#include "cub3d.h"

void	init_window(t_window *window)
{
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
	// init_data(window);
}