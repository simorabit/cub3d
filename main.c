/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 08:17:40 by moel-fat          #+#    #+#             */
/*   Updated: 2024/09/13 14:46:03 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Cub3d.h"

// void update_animation(t_window *window)
// {
//     static int current_image = 0;
//     static int frame_count = 0;
//     static void *current_img_ptr = NULL;
    
//     if (window->sprite->enabled)
//     {
//         if (frame_count % 2 == 0)
//         {
//             if (current_img_ptr != NULL && current_image > 0)
//             {
//                 mlx_delete_image(window->mlx_con, current_img_ptr);
//                 current_img_ptr = NULL;
//             }
//             current_img_ptr = window->sprite->sword_images[current_image];
//             mlx_image_to_window(window->mlx_con, current_img_ptr, 0, 0);
//             current_image++;
//             if (current_image >= 6)
//             {
//                 int i = 0;
//                 while (i < 6)
//                 {
//                     window->sprite->sword_images[i] = mlx_texture_to_image(window->mlx_con, window->sprite->sword[i]);
//                     if (!mlx_resize_image(window->sprite->sword_images[i], WIDTH, HEIGHT))
//                         ft_error(window->map, 6);
//                     i++;
//                 }
//                 window->sprite->enabled = false;
//                 current_image = 0;
//                 current_img_ptr = NULL;
//             }
//         }
//         if (frame_count > 10000)
//             frame_count = 0;
//         frame_count++;
//     }
// }

void re_load_images(t_window *window, int animation_type) {
    int i = 0;
    mlx_image_t **images;
    mlx_texture_t **textures;
    int num_frames;

    // Choose the correct animation based on the animation type
    if (animation_type == 1) {
        images = window->sprite->sword_images;
        textures = window->sprite->sword;
        num_frames = 6;  // Number of sword frames
    } else if (animation_type == 2) {
        images = window->sprite->pickaxe_images;
        textures = window->sprite->pickaxe;
        num_frames = 8;  // Number of pickaxe frames
    } else if (animation_type == 3) {
        images = window->sprite->axe_images;
        textures = window->sprite->axe;
        num_frames = 6;  // Number of axe frames
    } else {
        return; // Invalid animation type
    }

    // Reload images from textures
    while (i < num_frames) {
        images[i] = mlx_texture_to_image(window->mlx_con, textures[i]);
        if (!mlx_resize_image(images[i], WIDTH, HEIGHT))
            ft_error(window->map, 6);
        i++;
    }
}


void update_animation(t_window *window, mlx_image_t **images, int num_frames) {
    static int current_image = 0;
    static int frame_count = 0;
    static void *current_img_ptr = NULL;

    if (window->sprite->enabled) {
        if (frame_count % 2 == 0) {
            // Delete the previous image if it exists
            if (current_img_ptr != NULL) {
                mlx_delete_image(window->mlx_con, current_img_ptr);
                current_img_ptr = NULL;
            }

            // Show the current image frame
            current_img_ptr = images[current_image];
            mlx_image_to_window(window->mlx_con, current_img_ptr, 0, 0);

            current_image++;
            if (current_image >= num_frames) {
                current_image = 0;  // Reset to the first frame
                window->sprite->enabled = false;  // Disable animation once finished
                re_load_images(window, window->sprite->whatison);  // Reload images for the current animation
            }
        }

        // Limit frame count to avoid overflow
        if (frame_count > 10000)
            frame_count = 0;
        frame_count++;
    }
}


// void handle_animation_key(t_window *window)
// {
//     if (mlx_is_key_down(window->mlx_con, MLX_KEY_1) && !window->sprite->enabled) {
//         // Sword animation on key 1
//         window->sprite->enabled = true;
//         update_animation(window, window->sprite->sword_images, 6);
//     }
//     else if (mlx_is_key_down(window->mlx_con, MLX_KEY_2) && !window->sprite->enabled) {
//         // Pickaxe animation on key 2
//         window->sprite->enabled = true;
//         update_animation(window, window->sprite->pickaxe_images, 8);
//     }
//     else if (mlx_is_key_down(window->mlx_con, MLX_KEY_3) && !window->sprite->enabled) {
//         // Axe animation on key 3
//         window->sprite->enabled = true;
//         update_animation(window, window->sprite->axe_images, 6);
//     }
// }


void ft_sprint(void *param)
{
    t_window *window;
    window = (t_window *)param;
    // Trigger the correct animation based on key press
    if (mlx_is_key_down(window->mlx_con, MLX_KEY_1) && !window->sprite->enabled) {
        printf("1\n");
        // Sword animation on key 1
        window->sprite->enabled = true;
        window->sprite->current_animation_images = window->sprite->sword_images;
        window->sprite->num_frames = 6;
        window->sprite->whatison = 1;
    }
    else if (mlx_is_key_down(window->mlx_con, MLX_KEY_2) && !window->sprite->enabled) {
        printf("2\n");
        // Pickaxe animation on key 2
        window->sprite->enabled = true;
        window->sprite->current_animation_images = window->sprite->pickaxe_images;
        window->sprite->num_frames = 8;
        window->sprite->whatison = 2;
    }
    else if (mlx_is_key_down(window->mlx_con, MLX_KEY_3) && !window->sprite->enabled) {
        printf("3\n");
        // Axe animation on key 3
        window->sprite->enabled = true;
        window->sprite->current_animation_images = window->sprite->axe_images;
        window->sprite->num_frames = 6;
        window->sprite->whatison = 3;
    }
    // Always update the animation in every frame
    if (window->sprite->enabled) {
        update_animation(window, window->sprite->current_animation_images, window->sprite->num_frames);
    }
}



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
