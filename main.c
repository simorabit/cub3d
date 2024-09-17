/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 08:17:40 by moel-fat          #+#    #+#             */
/*   Updated: 2024/09/17 17:02:33 by mal-mora         ###   ########.fr       */
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

    // Reload images from textures
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

void ft_sprint(void *param)
{
    t_window *window;

    window = (t_window *)param;
    if (mlx_is_key_down(window->mlx_con, MLX_KEY_1) && !window->sprite->enabled)
    {
        window->sprite->enabled = true;
        window->sprite->current_animation_images = window->sprite->sword_images;
        window->sprite->num_frames = 6;
        window->sprite->whatison = 1;
    }
    else if (mlx_is_key_down(window->mlx_con, MLX_KEY_2) && !window->sprite->enabled)
    {
        window->sprite->enabled = true;
        window->sprite->current_animation_images = window->sprite->pickaxe_images;
        window->sprite->num_frames = 8;
        window->sprite->whatison = 2;
    }
    else if (mlx_is_key_down(window->mlx_con, MLX_KEY_3) && !window->sprite->enabled)
    {
        window->sprite->enabled = true;
        window->sprite->current_animation_images = window->sprite->axe_images;
        window->sprite->num_frames = 6;
        window->sprite->whatison = 3;
    }
    if (window->sprite->enabled)
        update_animation(window, window->sprite->current_animation_images, window->sprite->num_frames);
}



// void handle_mouse_rotation(t_window *window)
// {
//     int x, y;
//     static int last_x = 0;
    
//     mlx_get_mouse_pos(window->mlx_con, &x, &y);
//     window->player.rotation_angle += (x - last_x) * 0.01;
//     //   mlx_set_mouse_pos(window->mlx_con, HEIGHT / 2, WIDTH / 2);
//     last_x = x;
// }

void handle_mouse_rotation(t_window *window)
{
    int x, y;
    static int last_x = -1;
    int delta_x = 0;

    mlx_get_mouse_pos(window->mlx_con, &x, &y);
    if (last_x == -1)
    {
        window->player.rotation_angle = 0;
        last_x = x;
        delta_x = x - last_x;
    }
    window->player.rotation_angle += delta_x * 0.01;
    mlx_set_mouse_pos(window->mlx_con, WIDTH / 2, HEIGHT / 2);
    last_x = WIDTH / 2;
}

void    loop_func(void *param)
{
    t_window *window;

    window = (t_window *)param;
    update_player(window);
    handle_mouse_rotation(window);
    mlx_set_cursor_mode(window->mlx_con, MLX_MOUSE_HIDDEN);
    render(window);
}

static void display_window(t_window *window)
{
    init_window(window);
    init_player(&window->player, window->map);
    init_texture(window);
    init_sprint(window);
    window->sprite->enabled = false;
    mlx_loop_hook(window->mlx_con, loop_func, window);
    mlx_loop_hook(window->mlx_con, ft_sprint, window);
    listen_events(window);
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
    // print_map(map);
    window.map = map;
    display_window(&window);
    return 0;
}
