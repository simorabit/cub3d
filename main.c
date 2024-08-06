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

static void display_window(t_window *window)
{
    init_window(window);
    init_player(&window->player);
    read_map(window); 
    render(window);
    listen_events(window);
    mlx_loop(window->mlx_con);
}

int main(int argc, char *argv[])
{
    t_window window;
    t_map *map;

	if (argc != 2)
		ft_error(NULL, 1);
	// map = safe_malloc(sizeof (t_map));
	// // map_init(map);

	// check_read_map(argv[1], map);
    // window.map = map->map;
    (void)argc;
    (void)argv;
    display_window(&window);

    // mlx_t* mlx = mlx_init(WIDTH, HIGHT, "42Balls", true);
	// if (!mlx)
	// 	return 1;
	// mlx_image_t* img = mlx_new_image(mlx, 256, 256);
	// if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
	// 	return 1;

	// mlx_loop(mlx);
    return 0;
}
