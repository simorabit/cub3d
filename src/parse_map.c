/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:19:14 by moel-fat          #+#    #+#             */
/*   Updated: 2024/09/05 16:33:48 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

bool is_surrounded_by_walls(t_map *map)
{
    int		i; 
	int		j;
	char	c;

    j = 0;
	while ( j < map->width)
	{
        if (map->v_map[0][j] != '1' && map->v_map[0][j] != 'x')
            return false;
        if (map->v_map[map->height - 1][j] != '1' && map->v_map[map->height - 1][j] != 'x')
            return false;
		j++;
    }
	i = 0;
    while (i < map->height)
	{
        if (map->v_map[i][0] != '1' && map->v_map[i][0] != 'x')
            return false;
        if (map->v_map[i][map->width - 1] != '1' && map->v_map[i][map->width - 1] != 'x')
            return false;
		i++;
    }
	i = 0;
    while (i < map->height)
	{
		j = 0;
        while (j < map->width)
		{
            c = map->v_map[i][j];
            if (c != '1' && c != '0' && c != 'x' && c != 'N' && c != 'S' && c != 'E' && c != 'W')
                return false;
			j++;
        }
		i++;
    }
    return (true);
}

bool check_if_map_is_valid(t_map *map)
{
    int i = 0;
    while (i < map->height)
    {
        int j = 0;
        while (j < map->width)
        {
            if (map->v_map[i][j] == '0')
            {
                // Check top neighbor
                if (i > 0 && map->v_map[i - 1][j] == 'x')
                    return false;
                // Check bottom neighbor
                if (i < map->height - 1 && map->v_map[i + 1][j] == 'x')
                    return false;
                // Check left neighbor
                if (j > 0 && map->v_map[i][j - 1] == 'x')
                    return false;
                // Check right neighbor
                if ((j < map->width) - 1 && map->v_map[i][j + 1] == 'x')
                    return false;
            }
            j++;
        }
        i++;
    }
    return true;
}

void get_map_width(t_map *map)
{
	t_data *current;
	int max = 0;
	int len = 0;
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

void fill_map(t_map *map)
{
	int	i = 0;
	int j;
	get_map_width(map);
	map->width--;
	map->v_map = safe_malloc(sizeof(char *) * (map->height + 1));
	while(i < map->height)
	{
		j = 0;
		map->v_map[i] = safe_malloc(sizeof(char) * (map->width + 1));
		while(map->map[i][j] != '\0')
		{
			if(map->map[i][j] == ' ')
				map->v_map[i][j] = 'x';
			else
				map->v_map[i][j] = map->map[i][j];
			j++;
		}
		while(j < map->width)
		{
			map->v_map[i][j] = 'x';
			j++;
		}
		map->v_map[i][j] = '\0';
		i++;
	}
	map->v_map[i] = NULL;
}
