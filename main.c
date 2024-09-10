/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 08:17:40 by moel-fat          #+#    #+#             */
/*   Updated: 2024/09/10 19:24:59 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Cub3d.h"

// void    re_init_window(t_window *window)
// {
//     mlx_delete_image(window->mlx_con, window->img);
//     window->img = mlx_new_image(window->mlx_con, WIDTH, HEIGHT);
//     if (!window->img)
//         (write(2, "Error\n", 6), exit(1));
// 	mlx_image_to_window(window->mlx_con ,window->img, 0, 0);
// }


// void update_animation(t_window *window)
// {
//     int i = 0;
//     if (window->sprite->enabled)
//     {
//         while(i < 9)
//         {
//             mlx_image_to_window(window->mlx_con, window->sprite->sword_images[i], 0, 0);
//             i++;
//         }
//         window->sprite->enabled = false;
//     }
// }

void update_animation(t_window *window)
{
    static int current_image = 0;
    static int frame_count = 0;
    static void *current_img_ptr = NULL;
    
    if (window->sprite->enabled)
    {
        if (frame_count % 2 == 0)
        {
            if (current_img_ptr != NULL && current_image > 0)
            {
                mlx_delete_image(window->mlx_con, current_img_ptr);
                current_img_ptr = NULL;
            }
            current_img_ptr = window->sprite->sword_images[current_image];
            mlx_image_to_window(window->mlx_con, current_img_ptr, 0, 0);
            current_image++;
            if (current_image >= 9)
            {
                int i = 0;
                while (i < 9)
                {
                    window->sprite->sword_images[i] = mlx_texture_to_image(window->mlx_con, window->sprite->sword[i]);
                    if (!mlx_resize_image(window->sprite->sword_images[i], WIDTH, HEIGHT))
                        ft_error(window->map, 6);
                    i++;
                }
                window->sprite->enabled = false;
                current_image = 0;
                current_img_ptr = NULL;
            }
        }
        frame_count++;
    }
}

void ft_sprint(void *param)
{
    t_window *window;
    window = (t_window *)param;
    
    if (mlx_is_key_down(window->mlx_con, MLX_KEY_SPACE) && !window->sprite->enabled)
    {
        window->sprite->enabled = true;
        // update_animation(window);
    }
    update_animation(window);
}


void    loop_func(void *param)
{
    t_window *window;

    window = (t_window *)param;
    // re_init_window(window);// makayn lach re initw o katkhasar animation Í
    update_player(window); // Update player position here instead of in listen_events for better performance
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
