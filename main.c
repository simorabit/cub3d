/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 08:17:40 by moel-fat          #+#    #+#             */
/*   Updated: 2024/09/20 09:14:43 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/Cub3d.h"

void handle_mouse_rotation(t_window *window)
{
    int x;
    int y;
    int delta_x;
    
    mlx_get_mouse_pos(window->mlx_con, &x, &y);
    delta_x = (x - WIDTH / 2) / 8;
    window->player.rotation_angle += delta_x * 0.03;
    mlx_set_mouse_pos(window->mlx_con, WIDTH / 2, HEIGHT / 2);
}
// void    re_init_window(t_window *window)
// {
//     mlx_delete_image(window->mlx_con, window->img);
//     window->img = mlx_new_image(window->mlx_con, WIDTH, HEIGHT);
//     if (!window->img)
//         (write(2, "Error\n", 6), exit(1));
// 	mlx_image_to_window(window->mlx_con ,window->img, 0, 0);
// }
// void handle_mouse_rotation(t_window *window)
// {
//     int x, y;
//     static int last_x = 0;
//     mlx_get_mouse_pos(window->mlx_con, &x, &y);
//     window->player.rotation_angle += (x - last_x) * 0.01;
//     last_x = x;
// }
void    loop_func(void *param)
{
    t_window *window;

    window = (t_window *)param;
    update_player(window);
    if(window->is_mouse_on)
    {
        mlx_set_cursor_mode(window->mlx_con, MLX_MOUSE_HIDDEN);
        handle_mouse_rotation(window);
    }
    else
        mlx_set_cursor_mode(window->mlx_con, MLX_MOUSE_NORMAL);
    render(window);
}

static void display_window(t_window *window)
{
    init_window(window);
    init_player(&window->player, window->map);
    init_texture(window);
    init_sprint(window);
    window->sprite->enabled = false;
    mlx_set_mouse_pos(window->mlx_con, WIDTH / 2, HEIGHT / 2);
    mlx_loop_hook(window->mlx_con, loop_func, window);
    mlx_loop_hook(window->mlx_con, ft_sprint, window);
    mlx_key_hook(window->mlx_con, my_keyhook, window);
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
    window.map = map;
    display_window(&window);
    return 0;
}
