/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 08:17:40 by moel-fat          #+#    #+#             */
/*   Updated: 2024/09/16 13:25:37 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Cub3d.h"

void handle_mouse_rotation(t_window *window)
{
    int x, y;
    static int last_x = 0;

    mlx_get_mouse_pos(window->mlx_con, &x, &y);
    window->player.rotation_angle += (x - last_x) * 0.01;
    last_x = x;
}

void    loop_func(void *param)
{
    t_window *window;

    window = (t_window *)param;
    update_player(window);
    handle_mouse_rotation(window);
    render(window);
}

static void display_window(t_window *window)
{
    init_window(window);
    init_player(&window->player, window->map);
    init_texture(window);
    listen_events(window);
    init_sprint(window);
    window->sprite->enabled = false;
    mlx_loop_hook(window->mlx_con, loop_func, window);
    mlx_loop_hook(window->mlx_con, ft_sprint, window);
    mlx_loop(window->mlx_con);
}

void print_map(t_map *map)
{
    int i = 0;
    while (map->v_map[i] != NULL)
    {
        printf("%s\n", map->v_map[i]);
        i++;
    }
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
    // print_map(map);
    // window.map = map;
    // display_window(&window);
    return 0;
}
