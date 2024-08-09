/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 08:17:40 by moel-fat          #+#    #+#             */
/*   Updated: 2024/08/09 08:17:45 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Cub3d.h"

void read_map(t_window *window)
{
    int fd;
    int i;

    i = 0;
    fd = open("map", O_RDONLY);
    if (fd < 0)
        (perror("Failed to open map file"), exit(EXIT_FAILURE));
    window->map = malloc((MAP_NUM_ROWS + 1) * sizeof(char *));
    if (!window->map)
        (perror("Failed to read line from map"), exit(EXIT_FAILURE));
    while (i < MAP_NUM_ROWS)
    {
        window->map[i] = get_next_line(fd);
        if (!window->map[i])
            (perror("Failed to read line from map"), exit(EXIT_FAILURE));
        i++;
    }
    window->map[MAP_NUM_ROWS] = NULL;
    close(fd);
}

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
    render(window);
}

static void display_window(t_window *window)
{
    init_window(window);
    init_player(&window->player);
    read_map(window); 
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
    int i = 0;
    while (map->v_map[i])
    {
        printf("%s\n", map->v_map[i]);
        i++;
    }
    window.map = map->v_map;
    (void)argc;
    (void)argv;
    display_window(&window);

    return 0;
}
