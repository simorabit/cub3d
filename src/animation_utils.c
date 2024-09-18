/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:47:23 by moel-fat          #+#    #+#             */
/*   Updated: 2024/09/18 16:00:04 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

void	select_weapon(t_window *window, int frames, int weapen)
{
	window->sprite->enabled = true;
	window->sprite->num_frames = frames;
	window->sprite->whatison = weapen;
}

void	display_hand(t_window *window)
{
	if (window->sprite->hand_on == false)
	{
		window->sprite->current_animation_images = &window->sprite->Hand_image;
		window->sprite->num_frames = 1;
		window->sprite->enabled = true;
		window->sprite->hand_on = true;
	}
}
