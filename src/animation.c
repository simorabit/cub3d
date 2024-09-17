/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:07:20 by moel-fat          #+#    #+#             */
/*   Updated: 2024/09/17 14:20:49 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

void re_load_images(t_window *window, int animation_type)
{
    int i = 0;
    mlx_image_t **images;
    mlx_texture_t **textures;
    int num_frames;

    if (animation_type == 1)
    {
        images = window->sprite->sword_images;
        textures = window->sprite->sword;
        num_frames = 6;
    }
    else if (animation_type == 2)
    {
        images = window->sprite->pickaxe_images;
        textures = window->sprite->pickaxe;
        num_frames = 8;
    }
    else if (animation_type == 3)
    {
        images = window->sprite->axe_images;
        textures = window->sprite->axe;
        num_frames = 6;
    }
    else
        return ;
    while (i < num_frames)
    {
        images[i] = mlx_texture_to_image(window->mlx_con, textures[i]);
        if (!mlx_resize_image(images[i], WIDTH, HEIGHT))
            ft_error(window->map, 6);
        i++;
    }
}


void update_animation(t_window *window, mlx_image_t **images, int num_frames)
{
    static int current_image = 0;
    static int frame_count = 0;
    static void *current_img_ptr = NULL;

    if (window->sprite->enabled)
    {
        if (frame_count % 2 == 0)
        {
            if (current_img_ptr != NULL)
            {
                mlx_delete_image(window->mlx_con, current_img_ptr);
                current_img_ptr = NULL;
            }
            current_img_ptr = images[current_image];
            mlx_image_to_window(window->mlx_con, current_img_ptr, 0, 0);
            current_image++;
            if (current_image >= num_frames)
            {
                current_image = 0;
                window->sprite->enabled = false;
                re_load_images(window, window->sprite->whatison);
            }
        }
        if (frame_count > 10000)
            frame_count = 0;
        frame_count++;
    }
}

void    select_weapon(t_window *window, int frames, int weapen)
{
        window->sprite->enabled = true;
        window->sprite->num_frames = frames;
        window->sprite->whatison = weapen;
}

void    display_hand(t_window *window)
{
    if (window->sprite->hand_on == false)
    {
        window->sprite->current_animation_images = &window->sprite->Hand_image;
        window->sprite->num_frames = 1;
        window->sprite->enabled = true;
        window->sprite->hand_on = true;
    }
}

void ft_sprint(void *param)
{
    t_window *window;

    window = (t_window *)param;
    display_hand(window);
    if (mlx_is_key_down(window->mlx_con, MLX_KEY_1) && !window->sprite->enabled)
    {
        window->sprite->current_animation_images = window->sprite->sword_images;
        select_weapon(window, 6, 1);
    }
    else if (mlx_is_key_down(window->mlx_con, MLX_KEY_2) && !window->sprite->enabled)
    {
        window->sprite->current_animation_images = window->sprite->pickaxe_images;
        select_weapon(window, 8, 2);
    }
    else if (mlx_is_key_down(window->mlx_con, MLX_KEY_3) && !window->sprite->enabled)
    {
        window->sprite->current_animation_images = window->sprite->axe_images;
        select_weapon(window, 6, 3);
    }
    if (window->sprite->enabled)
        update_animation(window, window->sprite->current_animation_images, window->sprite->num_frames);
}
