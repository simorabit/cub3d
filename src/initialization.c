/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 08:18:07 by moel-fat          #+#    #+#             */
/*   Updated: 2024/09/13 12:07:31 by moel-fat         ###   ########.fr       */
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

void init_sword(t_window *window)
{
    int i;

    window->sprite = malloc(sizeof(t_sprite));
    if (!window->sprite)
        ft_error(window->map, 9);

    window->sprite->animation = malloc(sizeof(char *) * 6);
    window->sprite->sword = malloc(sizeof(mlx_texture_t *) * 6);
    window->sprite->sword_images = malloc(sizeof(mlx_image_t) * 6);

    if (!window->sprite->animation || !window->sprite->sword || !window->sprite->sword_images)
        ft_error(window->map, 9);

    const char *sword_paths[6] = {
    "assets/csword/1.png",
    "assets/csword/2.png",
    "assets/csword/3.png",
    "assets/csword/4.png",
    "assets/csword/5.png",
    "assets/csword/6.png"
    };

    i = 0;
    while (i < 6)
    {
        window->sprite->sword[i] = mlx_load_png(sword_paths[i]);
        if (!window->sprite->sword[i])
            ft_error(window->map, 10);

        window->sprite->sword_images[i] = mlx_texture_to_image(window->mlx_con, window->sprite->sword[i]);
        if (!window->sprite->sword_images[i] || !mlx_resize_image(window->sprite->sword_images[i], WIDTH, HEIGHT))
            ft_error(window->map, 10);

        i++;
    }
}
void init_pickaxe(t_window *window)
{
    int i;
    window->sprite->pickaxe = malloc(sizeof(mlx_texture_t *) * 8);
    window->sprite->pickaxe_images = malloc(sizeof(mlx_image_t) * 8);
    if (!window->sprite->pickaxe || !window->sprite->pickaxe_images)
        ft_error(window->map, 6);

    // Define the file paths for pickaxe animation frames
    const char *pickaxe_animation[8] = {
        "assets/cpickaxe/1.png",
        "assets/cpickaxe/2.png",
        "assets/cpickaxe/3.png",
        "assets/cpickaxe/4.png",
        "assets/cpickaxe/5.png",
        "assets/cpickaxe/6.png",
        "assets/cpickaxe/7.png",
        "assets/cpickaxe/8.png"
    };

    for (i = 0; i < 8; i++)
    {
        window->sprite->pickaxe[i] = mlx_load_png(pickaxe_animation[i]);
        if (!window->sprite->pickaxe[i])
            ft_error(window->map, 6);
        window->sprite->pickaxe_images[i] = mlx_texture_to_image(window->mlx_con, window->sprite->pickaxe[i]);
        if (!mlx_resize_image(window->sprite->pickaxe_images[i], WIDTH, HEIGHT))
            ft_error(window->map, 6);
    }
}

void init_axe(t_window *window)
{
    int i;
    window->sprite->axe = malloc(sizeof(mlx_texture_t *) * 6);
    window->sprite->axe_images = malloc(sizeof(mlx_image_t) * 6);
    if (!window->sprite->axe || !window->sprite->axe_images)
        ft_error(window->map, 6);

    // Define the file paths for axe animation frames
    const char *axe_animation[6] = {
        "assets/caxe/1.png",
        "assets/caxe/2.png",
        "assets/caxe/3.png",
        "assets/caxe/4.png",
        "assets/caxe/5.png",
        "assets/caxe/6.png"
    };

    for (i = 0; i < 6; i++)
    {
        window->sprite->axe[i] = mlx_load_png(axe_animation[i]);
        if (!window->sprite->axe[i])
            ft_error(window->map, 6);
        window->sprite->axe_images[i] = mlx_texture_to_image(window->mlx_con, window->sprite->axe[i]);
        if (!mlx_resize_image(window->sprite->axe_images[i], WIDTH, HEIGHT))
            ft_error(window->map, 6);
    }
}

void init_sprint(t_window *window)
{
    init_sword(window);
    init_pickaxe(window);
    init_axe(window);
    window->sprite->enabled = false;
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
