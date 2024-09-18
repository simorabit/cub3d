/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:19:14 by moel-fat          #+#    #+#             */
/*   Updated: 2024/09/18 11:21:28 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

bool	check_if_map_is_valid(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->v_map[i][j] == '0')
			{
				if (i > 0 && map->v_map[i - 1][j] == 'x')
					return (false);
				if (i < map->height - 1 && map->v_map[i + 1][j] == 'x')
					return (false);
				if (j > 0 && map->v_map[i][j - 1] == 'x')
					return (false);
				if ((j < map->width) - 1 && map->v_map[i][j + 1] == 'x')
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

static void	get_map_width(t_map *map)
{
	t_data	*current;
	int		max;
	int		len;

	max = 0;
	len = 0;
	current = map->data;
	while (current != NULL)
	{
		len = ft_strlen(current->data);
		if (len > max)
			max = len;
		current = current->next;
	}
	map->width = max;
}

static void	fill_map_data(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		map->v_map[i] = safe_malloc(sizeof(char) * (map->width + 1));
		while (map->map[i][j] != '\0')
		{
			if (map->map[i][j] == ' ')
				map->v_map[i][j] = 'x';
			else
				map->v_map[i][j] = map->map[i][j];
			j++;
		}
		while (j < map->width)
		{
			map->v_map[i][j] = 'x';
			j++;
		}
		map->v_map[i][j] = '\0';
		i++;
	}
	map->v_map[i] = NULL;
}

void	fill_map(t_map *map)
{
	get_map_width(map);
	map->width--;
	map->v_map = safe_malloc(sizeof(char *) * (map->height + 1));
	fill_map_data(map);
}
