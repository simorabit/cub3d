/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:40:59 by moel-fat          #+#    #+#             */
/*   Updated: 2024/09/16 13:10:09 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

void init_sword(t_window *window)
{
    int i;

    window->sprite = malloc(sizeof(t_sprite));
    if (!window->sprite)
        ft_error(window->map, 9);

    window->sprite->sword = malloc(sizeof(mlx_texture_t *) * 6);
    window->sprite->sword_images = malloc(sizeof(mlx_image_t) * 6);

    if (!window->sprite->sword || !window->sprite->sword_images)
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

void init_hand(t_window *window)
{
    window->sprite->Hand = mlx_load_png("assets/hand.png");
    window->sprite->Hand_image = mlx_texture_to_image(window->mlx_con, window->sprite->Hand);
    if (!window->sprite->Hand || !window->sprite->Hand_image)
        ft_error(window->map, 6);
    if(!mlx_resize_image(window->sprite->Hand_image, WIDTH, HEIGHT))
        ft_error(window->map, 6);
}

void init_sprint(t_window *window)
{
    // init_hand(window);
    init_sword(window);
    init_pickaxe(window);
    init_axe(window);
    window->sprite->enabled = false;
}