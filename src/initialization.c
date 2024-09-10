/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 08:18:07 by moel-fat          #+#    #+#             */
/*   Updated: 2024/09/10 19:01:59 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/Cub3d.h"

void init_player(t_player *player, t_map *map)
{
    //TODO set the player view based on the map
    player->x = (map->player_x * TILE_SIZE) + (TILE_SIZE / 2);
    player->y = (map->player_y * TILE_SIZE) + (TILE_SIZE / 2);
    player->width = 10;
    player->height = 10;
    player->walk_direction = 0;
    player->turn_direction = 0;
    player->strafe_direction = 0;
    player->walk_speed = 8;
    player->turn_speed = 4 * (M_PI / 180);
    if (map->player_dir == NORTH)
        player->rotation_angle = 3 * (M_PI / 2);
    else if (map->player_dir == EAST)
        player->rotation_angle = 0;
    else if (map->player_dir == SOUTH)
        player->rotation_angle = (M_PI / 2);
    else if (map->player_dir == WEST)
        player->rotation_angle = M_PI;
}

void	init_window(t_window *window)
{
	window->title = "CUB3D"; // Properly allocate and initialize window title
    if (!window->title)
    {
        perror("Error in allocation");
        exit(EXIT_FAILURE);
    }
	window->mlx_con = mlx_init(WIDTH, HEIGHT, window->title, false);
	if (!window->mlx_con)
		(perror("Error in allocation"), exit(EXIT_FAILURE));
	window->img = mlx_new_image(window->mlx_con, WIDTH, HEIGHT);
	
	if (!window->img)
	{
		mlx_delete_image(window->mlx_con, window->img);
		(perror("Error in allocation"), exit(EXIT_FAILURE));
	}
    window->width = window->map->width * TILE_SIZE;
    window->height = window->map->height * TILE_SIZE;
	mlx_image_to_window(window->mlx_con ,window->img, 0, 0);
    window->ceiling_color = convert_color(&window->map->floor);
    window->floor_color = convert_color(&window->map->ceiling);
}

void init_sprint(t_window *window)
{
    int i;
    window->sprite = malloc(sizeof(t_sprite));
    if (!window->sprite)
        ft_error(window->map, 6);

    window->sprite->animation = malloc(sizeof(char *) * 9);
    window->sprite->sword = malloc(sizeof(mlx_texture_t *) * 9);
    window->sprite->sword_images = malloc(sizeof(mlx_image_t) * 9);

    window->sprite->animation[0] = "assets/sword/sword0.png";
    window->sprite->animation[1] = "assets/sword/sword1.png";
    window->sprite->animation[2] = "assets/sword/sword2.png";
    window->sprite->animation[3] = "assets/sword/sword3.png";
    window->sprite->animation[4] = "assets/sword/sword4.png";
    window->sprite->animation[5] = "assets/sword/sword5.png";
    window->sprite->animation[6] = "assets/sword/sword6.png";
    window->sprite->animation[7] = "assets/sword/sword7.png";
    window->sprite->animation[8] = "assets/sword/sword8.png";
    i = 0;
    while (i < 9)
    {
        window->sprite->sword[i] = mlx_load_png(window->sprite->animation[i]);
        if (!window->sprite->sword[i])
            ft_error(window->map, 6);
        window->sprite->sword_images[i] = mlx_texture_to_image(window->mlx_con, window->sprite->sword[i]);
        if (!mlx_resize_image(window->sprite->sword_images[i], WIDTH, HEIGHT))
            ft_error(window->map, 6);
        i++;
    }
}


void init_texture(t_window *window)
{
    window->texture = malloc(sizeof(mlx_texture_t *) * 4);

    window->texture[NORTH] = mlx_load_png(window->map->no);
    window->texture[SOUTH] = mlx_load_png(window->map->so);
    window->texture[EAST] = mlx_load_png(window->map->ea);
    window->texture[WEST] = mlx_load_png(window->map->we);
    if (!window->texture[NORTH] || !window->texture[SOUTH] || !window->texture[EAST] || !window->texture[WEST])
        ft_error(window->map, 6);
}
