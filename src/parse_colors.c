/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:25:18 by moel-fat          #+#    #+#             */
/*   Updated: 2024/09/05 16:26:05 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

bool is_all_number(char *str)
{
	int	i;
	if(!str)
		return (false);
	i = 0;
	while(str[i] == ' ')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			break ;
		i++;
	}
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] != '\0')
		return (false);
	return (true);
}

void	get_rgb_value(char *rgb, t_map *map, char R)
{
	char **tmp;
	char *new_line;
	int i = 0;
	
	new_line = remove_new_line(rgb);
	tmp = ft_split(new_line + 1, ',');
	while(tmp[i] != NULL)
		i++;
	if (i != 3)
		ft_error(map, 7);
	if (R == 'F')
	{
		if(is_all_number(tmp[0]) == false)
			ft_error(map, 6);
		map->floor.r = ft_atoi(tmp[0]);
		if(is_all_number(tmp[1]) == false)
			ft_error(map, 6);
		map->floor.g = ft_atoi(tmp[1]);
		if(is_all_number(tmp[2]) == false)
			ft_error(map, 6);
		map->floor.b = ft_atoi(tmp[2]);
		if (map->floor.r < 0 || map->floor.r > 255 || map->floor.g < 0 || map->floor.g > 255 || map->floor.b < 0 || map->floor.b > 255)
			ft_error(map, 6);
	}
	else if (R == 'C')
	{
		if(is_all_number(tmp[0]) == false)
			ft_error(map, 6);
		map->ceiling.r = ft_atoi(tmp[0]);
		if(is_all_number(tmp[1]) == false)
			ft_error(map, 6);
		map->ceiling.g = ft_atoi(tmp[1]);
		if(is_all_number(tmp[2]) == false)
			ft_error(map, 6);
		map->ceiling.b = ft_atoi(tmp[2]);
		if (map->ceiling.r < 0 || map->ceiling.r > 255 || map->ceiling.g < 0 || map->ceiling.g > 255 || map->ceiling.b < 0 || map->ceiling.b > 255)
			ft_error(map, 6);
	}
	free(new_line);
	free_array(tmp);
}
