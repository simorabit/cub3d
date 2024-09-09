/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 08:17:40 by moel-fat          #+#    #+#             */
/*   Updated: 2024/08/26 13:09:53 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Cub3d.h"


void    re_init_window(t_window *window)
{
    mlx_delete_image(window->mlx_con, window->img);
    window->img = mlx_new_image(window->mlx_con, WIDTH, HEIGHT);
    if (!window->img)
        (write(2, "Error\n", 6), exit(1));
	mlx_image_to_window(window->mlx_con ,window->img, 0, 0);
}

void    loop_func(void *param)
{
    t_window *window;

    window = (t_window *)param;
    re_init_window(window);
    update_player(window); // Update player position here instead of in listen_events for better performance
    render(window);
}

static void display_window(t_window *window)
{
    init_window(window);
    init_player(&window->player, window->map);
    init_texture(window);
    listen_events(window);
    mlx_loop_hook(window->mlx_con, loop_func, window);
    mlx_loop(window->mlx_con);
}

int main(int argc, char *argv[])
{
    t_window window;
    t_map *map;

	if (argc != 2)
	ft_error(NULL, 1);
    map = safe_malloc(sizeof (t_map));
    map_init(map);
    check_read_map(argv[1], map);
    window.map = map;
    display_window(&window);
    return 0;
}
