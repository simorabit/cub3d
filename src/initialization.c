/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 08:18:07 by moel-fat          #+#    #+#             */
/*   Updated: 2024/09/16 13:25:01 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/Cub3d.h"

void init_player(t_player *player, t_map *map)
{
    player->x = (map->player_x * TILE_SIZE) + (TILE_SIZE / 2);
    player->y = (map->player_y * TILE_SIZE) + (TILE_SIZE / 2);
    player->width = 10;
    player->height = 10;
    player->walk_direction = 0;
    player->turn_direction = 0;
    player->strafe_direction = 0;
    player->walk_speed = 6;
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
	window->title = "CUB3D";
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
